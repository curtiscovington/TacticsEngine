//
//  RenderSystem.h
//  TacticsEngine
//
//  Created by Curtis Covington on 1/28/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#ifndef RenderSystem_h
#define RenderSystem_h

#include "System.h"
#include <vector>
#include "Component.h"
#include "GLSLProgram.h"
#include <memory>
#include <glm/vec4.hpp>
#include "Vertex.h"


namespace TacticsEngine {
    class Window;
    class Camera;
    enum class GlyphSortType {
        NONE,
        TEXTURE,
    };
    struct Glyph {
        GLuint texture;
        int depth;
        Vertex* topLeft;
        Vertex* topRight;
        Vertex* botLeft;
        Vertex* botRight;
        
        ~Glyph() {
            delete topLeft;
            delete topRight;
            delete botLeft;
            delete botRight;
        }
    };
    
    struct RenderBatch {
        GLuint offset;
        GLuint numVertices;
        GLuint texture;
        RenderBatch(GLuint offset, GLuint numVertices, GLuint texture) : offset(offset), numVertices(numVertices), texture(texture) {}
    };
    
    class RenderSystem : public System {
    public:
        RenderSystem();
        void init();
        void init(Camera* camera);
        void onEntitiesChanged();
        void update(float dt);
        void draw( const glm::vec2& pos,  const TextureComponent& tex, const glm::vec4& uv, int depth);
        void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
        void end();
        void render();
        void sortGlyphs();
    private:
        Camera* m_camera;
        
        std::unique_ptr<Window> m_window;
        GLSLProgram m_glslProgram;
        GLuint m_vao{0};
        GLuint m_vbo{0};
        std::vector<std::unique_ptr<Glyph>> m_glyphs;
        std::vector<RenderBatch> m_batches;
        GlyphSortType m_sortType;
        
        void createVertexArray();
        void createRenderBatches();
    };
}

#endif /* RenderSystem_h */
