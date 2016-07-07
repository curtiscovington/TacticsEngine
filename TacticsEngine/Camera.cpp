//
//  Camera.cpp
//  TacticsEngine
//
//  Created by Curtis Covington on 1/30/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace TacticsEngine {
    Camera::Camera() {};
    Camera::~Camera() {};
    
    void Camera::init(int width, int height) {
        m_width = width;
        m_height = height;
        m_ortho = glm::ortho(0.0f, (float)m_width, 0.0f, (float)m_height);
        //glm::ortho(<#T left#>, <#T right#>, <#T bottom#>, <#T top#>)
    }
    
    void Camera::update() {
        if (m_isDirty) {
            glm::vec3 translate{-m_pos.x, -m_pos.y,0.0f};
            m_transform = glm::translate(m_ortho,translate);
            glm::vec3 scale{m_scale, m_scale, 0.0f};
            m_transform = glm::scale(m_transform, scale);
            m_isDirty = false;
        }
    }
}
