//
//  EntityManager.cpp
//  TacticsEngine
//
//  Created by Curtis Covington on 1/26/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#include "EntityManager.h"
#include "SystemManager.h"
namespace TacticsEngine {
    EntityManager::EntityManager() : m_systemManager(new SystemManager(this)) {
   
        //_components.reserve(MAX_COMPONETS_PER_ENTITY);
    }
    
    EntityManager::~EntityManager() {
        
    }
    
    void EntityManager::update() {
        if (m_isDirty) {
            m_systemManager->dirty();
            m_isDirty = false;
        }
        for (int i = 0; i < m_entities.size(); i++) {
            if (!m_entities[i]->isAlive()) {
                
            }
        }
        
        
    }
    
    SystemManager* EntityManager::getSystemManager() {
        return m_systemManager;
    }
    
    void EntityManager::getEntities(std::vector<Entity*>* entities, const ComponentBitset& bitmask) {
        entities->clear();
        for (EntitiesIterator it = m_entities.begin(); it != m_entities.end(); it++) {
            
            if (it->second->hasComponent(bitmask)) {
                entities->emplace_back(it->second.get());
            }
        }
    }
    
}