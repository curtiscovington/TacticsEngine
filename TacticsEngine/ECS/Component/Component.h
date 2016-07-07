//
//  Component.h
//  TacticsEngine
//
//  Created by Curtis Covington on 1/26/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#ifndef Component_h
#define Component_h

namespace TacticsEngine {
    using EntityID = unsigned int;
    typedef unsigned int ComponentID;
    typedef unsigned int ComponentBitset;
    
    
    struct Component {
        static constexpr ComponentBitset COMPONENT_BITSET_NONE = 0u;
        
        Component() {};
        ~Component() {};
        EntityID entity;
        template <class C>
        static ComponentID getComponentID() {
//            static_assert(std::is_base_of<Component, C>::value, "C must derive from Component.");
            static ComponentID id = generateUniqueID();
            
            return id;
        }
        
        template <class C>
        static ComponentBitset getComponentBitmask() {
            return 1 << getComponentID<C>();
        }
        template <class First, class Second, class ... Rest>
        static ComponentBitset getComponentBitmask() {
            return getComponentBitmask<First>() | getComponentBitmask<Second, Rest...>();
        }

    private:
        static ComponentID generateUniqueID() {
            static ComponentID id{0u};
            return id++;
        }
    };
    
}

#include "PositionComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "BoundingBoxComponent.h"
#include "CollisionComponent.h"
#include "PhysicsComponent.h"

#endif /* Component_h */
