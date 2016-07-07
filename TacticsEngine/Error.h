//
//  Error.h
//  TacticsEngine
//
//  Created by Curtis Covington on 1/23/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#ifndef Error_h
#define Error_h

#include <string>

namespace TacticsEngine {
    enum class ErrorCodes {
        UNKNOWN,
        FAILED_TO_CREATE_WINDOW,
        FAILED_TO_CREATE_SHADER,
        FAILED_TO_COMPILE_SHADER,
        FAILED_TO_LINK_SHADERS,
        FAILED_TO_LOAD_FILE,
        ERROR_TO_MANY_COMPONENTS,
    };
    
    class Error {
    public:
        Error(){};
        static Error& getInstance() {
            static Error instance;
            return instance;
        }
        
        // Terminate program after printing error
        void fail(const ErrorCodes& e) const;
        void fail(const ErrorCodes& e, std::string details) const;
    
        //    Ensure the singleton can not be copied
        Error(Error const&) = delete;
        void operator=(Error const&) = delete;
    private:
        const char* errorCodeToString(const ErrorCodes& e) const;
    };
}
#endif /* Error_h */
