//
//  SystemManager.h
//  TacticsEngine
//
//  Created by Curtis Covington on 1/27/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#ifndef SystemManager_h
#define SystemManager_h

#include "Error.h"

#include <vector>
#include <memory>
#include <bitset>
#include "System.h"
#include "PhysicsSystem.h"
#include "RenderSystem.h"
#include "EntityManager.h"

namespace TacticsEngine {
    constexpr std::size_t MAX_SYSTEMS = 32;
   
    class SystemManager {
    public:
        SystemManager(EntityManager* entityManager);
        ~SystemManager();
        
        void init();
        void update(float dt);
        EntityManager* getEntityManager();
        void dirty();
        
        void addSystem(System* system);
        template <class T>
        T* addSystem(const ComponentBitset& requiredBitmask) {
            static_assert(std::is_base_of<System, T>::value, "T must derive from System.");
            _systems.emplace_back(new T());
            _systems.back()->setManager(this);
            _systems.back()->m_bitmask = requiredBitmask;//Component::getComponentBitmask<Reqs...>();
            _entityManager->getEntities(&_systems.back()->m_entities, _systems.back()->m_bitmask);
            return (T*)_systems.back().get();
        }
    private:
        EntityManager* _entityManager;
        std::vector<std::unique_ptr<System>> _systems;
        bool _isDirty;
    };
}

#endif /* SystemManager_h */
