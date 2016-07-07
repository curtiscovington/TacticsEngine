//
//  IOManager.h
//  TacticsEngine
//
//  Created by Curtis Covington on 1/27/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#ifndef IOManager_h
#define IOManager_h

#include <vector>
#include <string>

namespace TacticsEngine {
    
    class IOManager {
        
    public:
        static IOManager& getInstance() {
            static IOManager instance;
            return instance;
        }
        bool readFileToBuffer(const std::string& filePath, std::vector<unsigned char>& buffer);
        bool readTextFileToBuffer(const std::string& filePath, std::vector<unsigned char>& buffer);
    private:
        IOManager();
        ~IOManager();
    };
}
#endif /* IOManager_h */
