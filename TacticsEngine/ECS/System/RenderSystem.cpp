//
//  RenderSystem.cpp
//  TacticsEngine
//
//  Created by Curtis Covington on 1/28/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#include "RenderSystem.h"
#include <iostream>
#include "EntityManager.h"
#include "Component.h"
#include <vector>
#include "Window.h"
#include <OpenGL/gl3.h>
#include <algorithm>
#include "Camera.h"


namespace TacticsEngine {
    
    RenderSystem::RenderSystem() : m_window(new Window()) {
        
    }
    void RenderSystem::init() {
      
    }
    void RenderSystem::init(Camera* camera) {
        m_camera = camera;
        
        m_window->create("Title", camera->getWidth(), camera->getHeight());
        m_glslProgram.load("res/shaders/vertex.shader", "res/shaders/fragment.shader");
        createVertexArray();
    }
    
    void RenderSystem::update(float dt) {
        m_camera->update();
        if (m_entities.size() > 0) {
            begin();
            for (int i = 0; i < m_entities.size(); i++) {
                
                draw(m_entities[i]->getComponent<PositionComponent>()->pos, *m_entities[i]->getComponent<TextureComponent>(), glm::vec4(0.0f,0.0f,1.0f,1.0f), 2);
            }
            end();
            
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
            
            m_glslProgram.use();
            m_glslProgram.setUniform1f("time", 0);
            m_glslProgram.setUniformMatrix4fv("P", (m_camera->getTransform()));
            m_glslProgram.setUniform1i("tex", 0);
            glActiveTexture(GL_TEXTURE0);
            
            glClearColor(0.0f, 0, 1.0f, 1.0f);
            
            
            render();
            
            m_glslProgram.disable();
            
            m_window->swap();
        }
    }
    
    void RenderSystem::draw(const glm::vec2& pos, const TextureComponent& tex, const glm::vec4& uv, int depth) {
        Glyph* g = new Glyph();
        g->texture = (int)*tex.texture;
        g->depth = depth;
        
        float halfWidth = tex.width/2.0f;
        float halfHeight = tex.height/2.0f;
        float left = pos.x - halfWidth;
        float up = pos.y - halfHeight;
        float right = pos.x + halfWidth;
        float down = pos.y + halfHeight;
        glm::vec2 topLeft(left,up);
        glm::vec2 topRight(right,up);
        glm::vec2 botLeft(left,down);
        glm::vec2 botRight(right,down);
        
        g->topLeft = new Vertex(topLeft, glm::vec2(uv.x, uv.y + uv.w), tex.rgba);
        g->botLeft = new Vertex(botLeft, glm::vec2(uv.x, uv.y), tex.rgba);
        g->topRight = new Vertex(topRight, glm::vec2(uv.x + uv.z, uv.y + uv.w), tex.rgba);
        g->botRight = new Vertex(botRight, glm::vec2(uv.x + uv.z, uv.y), tex.rgba);
        
        
        
        m_glyphs.emplace_back(std::unique_ptr<Glyph>(g));
    }
    
    void RenderSystem::createVertexArray() {
        if (m_vao == 0) glGenVertexArrays(1, &m_vao);
        if (m_vbo == 0) glGenBuffers(1, &m_vbo);
        
        
        glBindVertexArray(m_vao);
        glBindBuffer (GL_ARRAY_BUFFER, m_vbo);
        
        
        glEnableVertexAttribArray (0);
        glEnableVertexAttribArray (1);
        glEnableVertexAttribArray (2);
        
        glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
        glVertexAttribPointer (1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, rgba));
        glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
        
        glBindVertexArray(0);
    }
    
    void RenderSystem::createRenderBatches() {
        std::vector<Vertex> vertices;
        vertices.resize(6 * m_glyphs.size());
        if (m_glyphs.empty()) return;
        
        
        int cv = 0;
        m_batches.emplace_back(0, 6, m_glyphs[0]->texture);
        vertices[cv++] = *m_glyphs[0]->topLeft;
        vertices[cv++] = *m_glyphs[0]->botLeft;
        vertices[cv++] = *m_glyphs[0]->botRight;
        vertices[cv++] = *m_glyphs[0]->botRight;
        vertices[cv++] = *m_glyphs[0]->topRight;
        vertices[cv++] = *m_glyphs[0]->topLeft;
        
        for (int i = 1; i < m_glyphs.size(); i++) {
            
            if (m_glyphs[i]->texture != m_glyphs[i - 1]->texture) {
                m_batches.emplace_back(cv, 6, m_glyphs[i]->texture);
            } else {
                m_batches.back().numVertices += 6;
            }
            vertices[cv++] = *m_glyphs[i]->topLeft;
            vertices[cv++] = *m_glyphs[i]->botLeft;
            vertices[cv++] = *m_glyphs[i]->botRight;
            vertices[cv++] = *m_glyphs[i]->botRight;
            vertices[cv++] = *m_glyphs[i]->topRight;
            vertices[cv++] = *m_glyphs[i]->topLeft;
        }
        
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        // Orphan buffer
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    
    void RenderSystem::begin(GlyphSortType sortType) {
        m_sortType = sortType;
        m_batches.clear();
        
        m_glyphs.clear();
    }
    void RenderSystem::end() {
        sortGlyphs();
        createRenderBatches();
    }
    void RenderSystem::render() {
        glBindVertexArray(m_vao);
        for (int i = 0; i < m_batches.size(); i++) {
            
            glBindTexture(GL_TEXTURE_2D, m_batches[i].texture);
            glDrawArrays(GL_TRIANGLES, m_batches[i].offset, m_batches[i].numVertices);
        }
        glBindVertexArray(0);
    }
    void RenderSystem::sortGlyphs() {
        switch (m_sortType) {
            case GlyphSortType::TEXTURE:
                std::stable_sort(m_glyphs.begin(), m_glyphs.end(),
                                 [](const std::unique_ptr<Glyph>& a, const std::unique_ptr<Glyph>& b) -> bool { return a->texture < b->texture; } );
                break;
            default:
                break;
        }
        
    }
}