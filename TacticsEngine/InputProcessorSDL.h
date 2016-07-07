//
//  InputProcessorSDL.hpp
//  TacticsEngine
//
//  Created by Curtis Covington on 1/24/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#ifndef InputProcessorSDL_h
#define InputProcessorSDL_h

#include "InputManager.h"
#include <map>
#include <SDL2/SDL.h>

namespace TacticsEngine {
    
    class InputProcessor {
    public:
        InputProcessor(InputManager* m) : _manager(m) {};
        virtual void process() = 0;
    protected:
        InputManager* _manager;
        
    };
    class InputProcessorSDL: public InputProcessor {
    public:
        InputProcessorSDL(InputManager* m);
        ~InputProcessorSDL();
        
        void process();
        KeyCode toKeyCode(unsigned int sdlKey);
    private:
        SDL_Event* _event;
        std::map<unsigned int, KeyCode> _keyMap;
    };
}

#endif /* InputProcessorSDL_h */
