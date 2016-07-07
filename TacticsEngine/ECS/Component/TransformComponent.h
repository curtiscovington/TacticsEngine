//
//  TransformComponent.h
//  TacticsEngine
//
//  Created by Curtis Covington on 1/30/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#ifndef TransformComponent_h
#define TransformComponent_h

#include "Component.h"
#include <OpenGL/gl3.h>

#include <string>

namespace TacticsEngine {
    struct TransformComponent : public Component {
        GLuint texture;
        int width;
        int height;
        
        TransformComponent() {
            
        }
       
        
        void init() {
          
        };
    };
}

#endif /* TransformComponent_h */
