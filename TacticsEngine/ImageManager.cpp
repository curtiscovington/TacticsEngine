//
//  ImageManager.cpp
//  TacticsEngine
//
//  Created by Curtis Covington on 1/27/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#include "ImageManager.h"
#include "lodepng.h"
#include "IOManager.h"
#include "Error.h"
#include <OpenGL/gl3.h>

namespace TacticsEngine {
    
    ImageManager::ImageManager() {};
    ImageManager::~ImageManager() {};
    
    PNG* ImageManager::loadPNG(const std::string filePath) {
        std::vector<unsigned char> buffer;
        PNG* ptr = new PNG();
        IOManager::getInstance().readFileToBuffer(filePath, buffer);
    
        unsigned long width, height;
        int error = decodePNG(ptr->png, width, height, &buffer[0], buffer.size());
        if (error != 0) {
            Error::getInstance().fail(ErrorCodes::UNKNOWN, "lodePNG error code" + std::to_string(error));
        }
        ptr->width = width;
        ptr->height = height;
        
        return ptr;
    }

}