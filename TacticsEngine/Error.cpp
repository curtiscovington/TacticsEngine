//
//  Error.cpp
//  TacticsEngine
//
//  Created by Curtis Covington on 1/23/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#include "Error.h"
#include <stdlib.h>
#include <SDL2/SDL.h>

namespace TacticsEngine {
    
    void Error::fail(const ErrorCodes& e) const {
        std::printf("Error: %s\n", errorCodeToString(e));
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    
    void Error::fail(const ErrorCodes& e, std::string details) const {
        std::printf("Error: %s\n%s\n", errorCodeToString(e), details.c_str());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    
    const char* Error::errorCodeToString(const ErrorCodes &e) const{
        
        switch (e) {
            default:
            case ErrorCodes::UNKNOWN:
                return "Unknown error.";
                break;
            case ErrorCodes::FAILED_TO_CREATE_WINDOW:
                return "Failed to create window.";
                break;
            case ErrorCodes::FAILED_TO_CREATE_SHADER:
                return "Failed to create shader.";
                break;
            case ErrorCodes::FAILED_TO_COMPILE_SHADER:
                return "Failed to compile shader.";
                break;
            case ErrorCodes::FAILED_TO_LOAD_FILE:
                return "Failed to load file.";
                break;
            case ErrorCodes::ERROR_TO_MANY_COMPONENTS:
                return "Too many components.";
                break;
            
        }
    }
}