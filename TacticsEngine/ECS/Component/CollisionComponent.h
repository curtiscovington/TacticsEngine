//
//  CollisionComponent.h
//  TacticsEngine
//
//  Created by Curtis Covington on 2/1/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#ifndef CollisionComponent_h
#define CollisionComponent_h

#include "Component.h"
#include <glm/glm.hpp>

namespace TacticsEngine {
    struct Shape {
        float x{0}, y{0};
        Shape();
        Shape(float x, float y) : x(x), y(y) {};
    };
    struct Rectangle : public Shape {
        float width{0}, height{0};
        Rectangle() : Shape() {};
        Rectangle(float x, float y, float width, float height)
            : Shape(x,y), width(width), height(height) {};
    };
    struct Circle : public Shape {
        float radius{0};
        Circle() {};
        Circle(float x, float y, float radius)
        : Shape(x,y), radius(radius) {};
    };
    
    struct CollisionComponent : public Component{
    private:
        bool m_isRect = true;
        bool m_isCircle = false;
    public:
        Rectangle rect{0,0,0,0};
        Circle circle{0,0,0}; // x, y, radius
        CollisionComponent() {};
        CollisionComponent(float x, float y, float width, float height) : rect(x,y,width,height) {};
        CollisionComponent(Rectangle rect) : rect(rect) {};
        
        CollisionComponent(Circle circle) : circle(circle), m_isCircle(true) {}
        
        bool isRect() const {
            return m_isRect;
        }
        
        bool isCircle() const {
            return m_isCircle;
        }
    };
}


#endif /* CollisionComponent_h */
