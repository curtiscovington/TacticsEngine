//
//  Entity.cpp
//  TacticsEngine
//
//  Created by Curtis Covington on 1/30/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#include "Entity.h"
#include "EntityManager.h"
#include "Component.h"
namespace TacticsEngine {
   
    
        
    Entity::Entity(EntityManager* manager) : m_manager(manager) {};
    
    void Entity::destroy() { m_isAlive = false; };
    
    EntityID Entity::getID() {
        return m_id;
    }
    EntityID Entity::generateUniqueID() {
        static EntityID id{0};
        return id++;
    }
    
    void Entity::dirty() {
        m_manager->dirty();
    }
    
    bool Entity::isAlive() const {
        return m_isAlive;
    }
}