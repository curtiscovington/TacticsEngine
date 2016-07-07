//
//  Window.h
//  TacticsEngine
//
//  Created by Curtis Covington on 1/23/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#ifndef Window_h
#define Window_h
#include <SDL2/SDL.h>
#include <string>

namespace TacticsEngine {
    
enum WindowFlags {
    FULLSCREEN = 0x1,
    BORDERLESS = 0x2,
    OPENGL = 0x4,
};

class Window {
public:
    Window();
    ~Window();
    int create(const std::string& title, const int w, const int h, const Uint32 flags = 0);
    SDL_Window* getSDL_Window() const;
    void swap();
    
    int getWidth() const { return _width; };
    int getHeight() const { return _height; };
private:
    SDL_Window* _window;
    SDL_GLContext _glContext;
    int _width;
    int _height;
    
    Uint32 convertFlagsToSDLWindowFlags(const Uint32 flags);
};
    
}
#endif /* Window_h */
