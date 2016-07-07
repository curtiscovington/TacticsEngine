//
//  IOManager.cpp
//  TacticsEngine
//
//  Created by Curtis Covington on 1/27/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#include "IOManager.h"
#include "Error.h"
#include <fstream>

namespace TacticsEngine {
    IOManager::IOManager() {};
    IOManager::~IOManager() {};
    
    
    bool IOManager::readFileToBuffer(const std::string& filePath, std::vector<unsigned char>& buffer) {
        std::ifstream file(filePath, std::ios::binary | std::ios::ate);
        if (file.fail()) {
            Error::getInstance().fail(ErrorCodes::FAILED_TO_LOAD_FILE, filePath);
            return false;
        }
        
        int size = (int)file.tellg();
        file.seekg(0, std::ios::beg);
        
        buffer.resize(size);
        file.read((char*)&(buffer[0]), size);
        
        file.close();
        
        return true;
    }
    
    bool IOManager::readTextFileToBuffer(const std::string& filePath, std::vector<unsigned char>& buffer) {
        if (readFileToBuffer(filePath, buffer)) {
            buffer.emplace_back('\0');
            return true;
        }
        
        return false;
    }
}
