//
//  InputProcessorSDL.cpp
//  TacticsEngine
//
//  Created by Curtis Covington on 1/24/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#include "InputProcessorSDL.h"


namespace TacticsEngine {
    InputProcessorSDL::InputProcessorSDL(InputManager* m) : InputProcessor(m) {
        // initialzie the map
        _keyMap[SDLK_0] = KeyCode::NUM_0;
        _keyMap[SDLK_1] = KeyCode::NUM_1;
        _keyMap[SDLK_2] = KeyCode::NUM_2;
        _keyMap[SDLK_3] = KeyCode::NUM_3;
        _keyMap[SDLK_4] = KeyCode::NUM_4;
        _keyMap[SDLK_5] = KeyCode::NUM_5;
        _keyMap[SDLK_6] = KeyCode::NUM_6;
        _keyMap[SDLK_7] = KeyCode::NUM_7;
        _keyMap[SDLK_8] = KeyCode::NUM_8;
        _keyMap[SDLK_9] = KeyCode::NUM_9;
        _keyMap[SDLK_a] = KeyCode::A;
        _keyMap[SDLK_b] = KeyCode::B;
        _keyMap[SDLK_c] = KeyCode::C;
        _keyMap[SDLK_d] = KeyCode::D;
        _keyMap[SDLK_e] = KeyCode::E;
        _keyMap[SDLK_f] = KeyCode::F;
        _keyMap[SDLK_g] = KeyCode::G;
        _keyMap[SDLK_h] = KeyCode::H;
        _keyMap[SDLK_i] = KeyCode::I;
        _keyMap[SDLK_j] = KeyCode::J;
        _keyMap[SDLK_k] = KeyCode::K;
        _keyMap[SDLK_l] = KeyCode::L;
        
        _keyMap[SDLK_m] = KeyCode::M;
        _keyMap[SDLK_n] = KeyCode::N;
        _keyMap[SDLK_o] = KeyCode::O;
        _keyMap[SDLK_p] = KeyCode::P;
        _keyMap[SDLK_q] = KeyCode::Q;
        _keyMap[SDLK_r] = KeyCode::R;
        _keyMap[SDLK_s] = KeyCode::S;
        _keyMap[SDLK_t] = KeyCode::T;
        _keyMap[SDLK_u] = KeyCode::U;
        _keyMap[SDLK_v] = KeyCode::V;
        _keyMap[SDLK_w] = KeyCode::W;
        _keyMap[SDLK_x] = KeyCode::X;
        _keyMap[SDLK_y] = KeyCode::Y;
        _keyMap[SDLK_z] = KeyCode::Z;
        _keyMap[SDLK_SPACE] = KeyCode::SPACE;
        _keyMap[SDLK_LSHIFT] = KeyCode::SHIFT;
        
        _keyMap[SDL_BUTTON_LEFT] = KeyCode::MOUSE_LEFT;
        _keyMap[SDL_BUTTON_RIGHT] = KeyCode::MOUSE_RIGHT;
    }
    
    InputProcessorSDL::~InputProcessorSDL() {
        
    }
    
    void InputProcessorSDL::process() {
        SDL_PumpEvents();
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    _manager->press(KeyCode::QUIT);
                case SDL_KEYDOWN:
                    _manager->press(toKeyCode(e.key.keysym.sym));
                    break;
                case SDL_KEYUP:
                    _manager->release(toKeyCode(e.key.keysym.sym));
                    break;
                case SDL_MOUSEMOTION:
                    _manager->setMousePosition(e.motion.x, e.motion.y);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    _manager->press(toKeyCode(e.button.button));
                    break;
                case SDL_MOUSEBUTTONUP:
                    _manager->release(toKeyCode(e.button.button));
                    break;
            }
        }
    }
    
    KeyCode InputProcessorSDL::toKeyCode(unsigned int sdlKey) {
        auto it = _keyMap.find(sdlKey);
        if (it != _keyMap.end()) {
            return it->second;
        }
        return KeyCode::UNKNOWN;
    }
}