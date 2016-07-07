//
//  System.h
//  TacticsEngine
//
//  Created by Curtis Covington on 1/27/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#ifndef System_h
#define System_h

#include <vector>
#include "Component.h"


namespace TacticsEngine {
    class EntityManager;
    class Entity;
    class SystemManager;
    using SystemID = unsigned int;
    class System {
        friend class SystemManager;
    public:
        System();
        ~System();
        
        virtual void init() = 0;
        virtual void update(float dt) = 0;
        void onEntitiesChanged() {};
        
        EntityManager* getEntityManager();
        ComponentBitset getBitmask() const { return m_bitmask; };
        ComponentBitset getOptionalBitmask() const { return m_optionalBitmask; };
        
    protected:
        SystemManager* m_manager;
        EntityManager* m_entityManager;
        std::vector<Entity*> m_entities;
        ComponentBitset m_bitmask;
        ComponentBitset m_optionalBitmask;
        bool m_isRunning;
     
        //std::vector<std::vector<Components>*> _groups;
        
        
    private:
        void setManager(SystemManager* manager) { m_manager = manager; };
        void setEntityManager(EntityManager* manager) { m_entityManager = manager; };
        
        SystemID generateUniqueComponentID() {
            static SystemID id{0u};
            return id++;
        }
        
        template <typename T>
        static SystemID getID() {
            static SystemID id{0u};
            return id++;
        }
    };
}

#include "RenderSystem.h"

#endif /* System_h */
