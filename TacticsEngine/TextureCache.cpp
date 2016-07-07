//
//  TextureCache.cpp
//  TacticsEngine
//
//  Created by Curtis Covington on 1/30/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#include "TextureCache.h"
#include "ImageManager.h"
#include "Texture.h"

namespace TacticsEngine {
    TextureCache::TextureCache() {
        
    }
    TextureCache::~TextureCache() {
        
    }
    
    GLTexture* TextureCache::getTexture(std::string filePath){
        auto it = _textureMap.find(filePath);
        if (it != _textureMap.end()) {
            
            return it->second.get();
        } else {
            auto p = _textureMap.insert(std::make_pair(
                                              filePath,
                                              std::unique_ptr<GLTexture>(new GLTexture(filePath))
                                              )
                                            );
            return p.first->second.get();
        }
    }
}