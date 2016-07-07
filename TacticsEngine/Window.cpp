//
//  Window.cpp
//  TacticsEngine
//
//  Created by Curtis Covington on 1/23/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#include "Window.h"
#include "Error.h"
#include <SDL2/SDL.h>
#include <OpenGL/gl3.h>

namespace TacticsEngine {
    
    Window::Window() : _window(nullptr), _width(0), _height(0){
        
    }
    
    Window::~Window() {
        SDL_GL_DeleteContext(_glContext);
        SDL_DestroyWindow(_window);
    }
    
    SDL_Window* Window::getSDL_Window() const {
        return _window;
    }
    
    void Window::swap() {
        SDL_GL_SwapWindow(_window);
    }
    
    int Window::create(const std::string& title, const int w, const int h, const Uint32 flags) {
        _width = w;
        _height = h;
        
        _window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, convertFlagsToSDLWindowFlags(flags));
        
        if (_window == 0) {
            Error::getInstance().fail(ErrorCodes::FAILED_TO_CREATE_WINDOW);
        }
        
        _glContext = SDL_GL_CreateContext(_window);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
        return 0;
    }
    
    Uint32 Window::convertFlagsToSDLWindowFlags(const Uint32 flags) {
        Uint32 f = 0;
        f |= SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
        
        if (flags & WindowFlags::FULLSCREEN) {
            f |= SDL_WINDOW_FULLSCREEN;
        }
        if (flags & WindowFlags::BORDERLESS) {
            f |= SDL_WINDOW_BORDERLESS;
        }
        
        
        return f;
    }

}