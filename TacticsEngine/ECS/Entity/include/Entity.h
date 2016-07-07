//
//  Entity.h
//  TacticsEngine
//
//  Created by Curtis Covington on 1/28/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#ifndef Entity_h
#define Entity_h

#include <array>
#include <vector>
#include <bitset>
#include <memory>
#include "Component.h"
#include "Error.h"
namespace TacticsEngine {
    class EntityManager;
    using ComponentPtr = std::unique_ptr<Component>;
    typedef unsigned int EntityID;
    typedef unsigned int ComponetID;
    
    constexpr std::size_t MAX_COMPONETS_PER_ENTITY = 32;
    
    class Entity {
        friend class EntityManager;
    public:
        EntityID getID();
        
        bool isAlive() const;
        void dirty();
        
        template <class C, typename ... Args>
        C* addComponent(Args... args) {
            ComponentID id = Component::getComponentID<C>();
            if (id > MAX_COMPONETS_PER_ENTITY) {
                Error::getInstance().fail(ErrorCodes::ERROR_TO_MANY_COMPONENTS);
            }
            
             ComponentPtr ptr = ComponentPtr(new C(std::forward<Args>(args)...));
    
            m_components[id] = std::move(ptr);
            m_bitmask |= Component::getComponentBitmask<C>();
            dirty();
            return static_cast<C*>(m_components[id].get());
        }
        template <class C>
        C* getComponent() const {
            ComponentID id = Component::getComponentID<C>();
            return static_cast<C*>(m_components[id].get());
        }
        
        bool hasComponent(ComponentBitset mask) {
            return (m_bitmask & mask) == mask;
        }
        
        template <class C>
        bool hasComponent() {
            ComponentBitset mask = Component::getComponentBitmask<C>();
            
            return (m_bitmask & mask) == mask;
        }
        template <class First, class Second, typename ... Rest>
        bool hasComponent() {
            return hasComponent<First>() && hasComponent<Second, Rest...>();
        }
    private:
        EntityID m_id = generateUniqueID();
        EntityManager* m_manager;
        std::array<ComponentPtr, MAX_COMPONETS_PER_ENTITY> m_components;

        bool m_isAlive;

        ComponentBitset m_bitmask;
        
        Entity(EntityManager* manager);
        void destroy();
    
        EntityID generateUniqueID();
    };
}
#endif /* Entity_h */
