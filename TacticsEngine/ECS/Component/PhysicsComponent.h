//
//  PhysicsComponent.h
//  TacticsEngine
//
//  Created by Curtis Covington on 2/1/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#ifndef PhysicsComponent_h
#define PhysicsComponent_h

#include "Component.h"
#include <glm/glm.hpp>

namespace TacticsEngine {
    struct PhysicsComponent : public Component {
        glm::vec2 velocity{0,0};
        bool isStatic{false};      // Can forces act upon the velocity
        
        PhysicsComponent()  {};
        PhysicsComponent(float x, float y, bool isStatic = false) : velocity(x,y), isStatic(isStatic){};
        PhysicsComponent(glm::vec2 velocity, bool isStatic = false) : velocity(velocity), isStatic(isStatic){};
        void addForce(const glm::vec2& force) {
            if (!isStatic) {
                velocity += force;
            }
        }
    };
}

#endif /* PhysicsComponent_h */
