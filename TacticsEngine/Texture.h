//
//  Texture.h
//  TacticsEngine
//
//  Created by Curtis Covington on 1/30/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#ifndef Texture_h
#define Texture_h

#include <OpenGL/gl3.h>
#include <ImageManager.h>

#include <string>

namespace TacticsEngine {
    struct GLTexture {
        GLuint texture;
        long width;
        long height;
        
        GLTexture() {
            
        }
        GLTexture(const std::string& filePath) {
            init(filePath);
        }
        ~GLTexture() {
            
        }
        
        void init(const std::string& filePath) {
            PNG* png = ImageManager::getInstance().loadPNG(filePath);
            width = png->width;
            height = png->height;
            
            glGenTextures(1, &(texture));
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (int)width, (int)height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(png->png[0]));
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glGenerateMipmap(GL_TEXTURE_2D);
            
            glBindTexture(GL_TEXTURE_2D, 0);
            delete png;
        };
        
        operator int() const { return texture; }
    };
}

#endif /* Texture_h */
