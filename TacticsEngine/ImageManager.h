//
//  ImageManager.h
//  TacticsEngine
//
//  Created by Curtis Covington on 1/27/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#ifndef ImageManager_h
#define ImageManager_h
#include <string>
#include <vector>

namespace TacticsEngine {
    struct PNG {
        std::vector<unsigned char> png;
        long width;
        long height;
    };
    class ImageManager {
    public:
        static ImageManager& getInstance() {
            static ImageManager instance;
            return instance;
        }
        //    Ensure the singleton can not be copied
        ImageManager(ImageManager const&) = delete;
        void operator=(ImageManager const&) = delete;
        
        PNG* loadPNG(const std::string filePath);
    private:
        ImageManager();
        ~ImageManager();
    };
}

#endif /* ImageManager_h */
