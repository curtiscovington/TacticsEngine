//
//  Vertex.h
//  TacticsEngine
//
//  Created by Curtis Covington on 1/26/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#ifndef Vertex_h
#define Vertex_h

#include <glm/glm.hpp>

namespace TacticsEngine {
    struct Color {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
        
        Color(unsigned char r = 255, unsigned char g = 255, unsigned char b = 255, unsigned char a = 255) : r(r), g(g), b(b), a(a) {}
    };
    struct Vertex {
        glm::vec2 pos;
        glm::vec2 uv;
        Color rgba;
        Vertex() {};
        Vertex(glm::vec2 pos, glm::vec2 uv, Color rgba = Color()) : pos(pos), rgba(rgba), uv(uv) {}
        
    };
}


#endif /* Vertex_h */
