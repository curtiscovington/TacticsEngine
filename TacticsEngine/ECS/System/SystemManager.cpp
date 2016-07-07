//
//  SystemManager.cpp
//  TacticsEngine
//
//  Created by Curtis Covington on 1/27/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#include "SystemManager.h"
#include "Entity.h"
#include "EntityManager.h"

namespace TacticsEngine {
    SystemManager::SystemManager(EntityManager* entityManager) : _entityManager(entityManager), _isDirty(false) {
    
    }
    SystemManager::~SystemManager() {
        
    }
    
    void SystemManager::init() {
        for (int i = 0; i < _systems.size(); i++) {
            _systems[i]->init();
        }
    }
    
    void SystemManager::update(float dt) {
        for (int i = 0; i < _systems.size(); i++) {
            if (_isDirty) {
                _entityManager->getEntities(&_systems[i]->m_entities,_systems[i]->m_bitmask);
                _systems[i]->onEntitiesChanged();
            }
            _systems[i]->update(dt);
        }
        
        if (_isDirty) _isDirty = false;
    }
    
    EntityManager* SystemManager::getEntityManager() {
        return _entityManager;
    }
    
    void SystemManager::dirty() {
        _isDirty = true;
    }
    
}