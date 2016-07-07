//
//  TextureCache.h
//  TacticsEngine
//
//  Created by Curtis Covington on 1/30/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#ifndef TextureCache_h
#define TextureCache_h
#include <map>
#include <string>
#include <memory>


namespace TacticsEngine {
    class GLTexture;
    class TextureCache {
    public:
        TextureCache();
        ~TextureCache();
        GLTexture* getTexture(std::string filePath);
    private:
        std::map<std::string, std::unique_ptr<GLTexture>> _textureMap;
    };
}

#endif /* TextureCache_h */
