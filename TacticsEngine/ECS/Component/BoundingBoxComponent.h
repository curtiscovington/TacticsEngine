//
//  BoundingBoxComponent.h
//  TacticsEngine
//
//  Created by Curtis Covington on 1/31/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#ifndef BoundingBoxComponent_h
#define BoundingBoxComponent_h

#include "Component.h"
#include "Texture.h"
#include "Vertex.h"
#include <OpenGL/gl3.h>
#include <ImageManager.h>

#include <string>

namespace TacticsEngine {
    struct BoundingBoxComponent : public Component {
        
        float width;
        float height;
  
        
        BoundingBoxComponent(float width, float height) : width(width), height(height) {}
        
        BoundingBoxComponent() {
            
        }
        ~BoundingBoxComponent() {}
        
    };
}


#endif /* BoundingBoxComponent_h */
