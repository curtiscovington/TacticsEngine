//
//  PositionComponent.h
//  TacticsEngine
//
//  Created by Curtis Covington on 1/26/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#ifndef PositionComponent_h
#define PositionComponent_h
#include "Component.h"
#include <glm/glm.hpp>
namespace TacticsEngine {
    struct PositionComponent : public Component {
        glm::vec2 pos;
        PositionComponent() :  pos(0,0){};
        PositionComponent(float x, float y) : pos(x,y) {};
        PositionComponent(glm::vec2 pos) : pos(pos) {};
    };
}

#endif /* PositionComponent_h */
