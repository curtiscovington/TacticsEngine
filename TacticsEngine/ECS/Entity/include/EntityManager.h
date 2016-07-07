//
//  EntityManager.h
//  TacticsEngine
//
//  Created by Curtis Covington on 1/26/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#ifndef EntityManager_h
#define EntityManager_h
#include <iostream>
#include <vector>
#include <memory>
#include <bitset>
#include <map>

#include "Component.h"
#include "Entity.h"



namespace TacticsEngine {
    class SystemManager;
    using EntityPtr = std::unique_ptr<Entity>;
    using EntityID = unsigned int;
    using ComponetID = unsigned int;
    using EntitiesIterator = std::map<int, std::unique_ptr<Entity>>::iterator;
    
    
    class EntityManager;
    class Entity;
    
    class EntityManager {
    public:
        EntityManager();
        ~EntityManager();
        
        void update();
        SystemManager* getSystemManager();
        
        Entity* addEntity() {
            EntityPtr ptr = EntityPtr(new Entity(this));
            auto p = m_entities.insert(std::pair<EntityID, EntityPtr>(ptr->getID(), std::move(ptr)));
            return p.first->second.get();
        }
        
        template <class ... C>
        Entity* addEntity() {
            EntityPtr ptr = EntityPtr(new Entity(this));
            auto p = m_entities.insert(std::pair<EntityID, EntityPtr>(ptr->getID(), std::move(ptr)));
            
            p.first->second->addComponent<C...>();
            dirty();
            return p.first->second.get();
        }
        
        void getEntities(std::vector<Entity*>* entities, const ComponentBitset& bitmask);
        
        template <class ... C>
        void getEntities(std::vector<Entity*>* entities) {
            auto bitmask = Component::getComponentBitmask<C...>();
            
            getEntities(entities, bitmask);
            //return entities;
        }
        
        void dirty() {
            m_isDirty = true;
        }
    private:
        
        std::map<int, std::unique_ptr<Entity>> m_entities;
   
        SystemManager* m_systemManager;
        bool m_isDirty = false;
        
      
        
    };
}

#endif /* EntityManager_h */
