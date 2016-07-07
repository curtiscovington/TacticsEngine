//
//  Camera.hpp
//  TacticsEngine
//
//  Created by Curtis Covington on 1/30/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace TacticsEngine {
    class Camera {
    public:
        Camera();
        ~Camera();
        
        void init(int width, int height);
        void update();
        
        void setScale(float scale) { if (scale < 0.5f ) scale = 0.5f; m_scale = scale; m_isDirty = true; };
        float getScale() const { return m_scale; };
        
        void setPosition(const glm::vec2 pos) { m_pos = pos; m_isDirty = true; };
        
        glm::mat4 getTransform() { return m_transform; };
        
        glm::vec2 getPosition() const { return m_pos; };
        
        int getWidth() const { return m_width; };
        int getHeight() const { return m_height; };
    private:
        int m_width;
        int m_height;
        float m_scale = 1.0f;
        glm::vec2 m_pos{0.0f};
        glm::mat4 m_transform{1.0f};
        bool m_isDirty{true};
        glm::mat4 m_ortho{1.0f};
    };
}
#endif /* Camera_hpp */
