//
//  TextureComponent.h
//  TacticsEngine
//
//  Created by Curtis Covington on 1/26/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#ifndef TextureComponent_h
#define TextureComponent_h
#include "Component.h"
#include "Texture.h"
#include "Vertex.h"
#include <OpenGL/gl3.h>
#include <ImageManager.h>

#include <string>

namespace TacticsEngine {
    struct TextureComponent : public Component {
        GLTexture* texture;
        float width;
        float height;
        Color rgba;
        
        TextureComponent() {}

        TextureComponent(GLTexture* texture, float width, float height, Color rgba = Color()) :
        texture(texture), width(width), height(height), rgba(rgba) {
            
        }
        ~TextureComponent() {}

    };
}

#endif /* TextureComponent_h */
