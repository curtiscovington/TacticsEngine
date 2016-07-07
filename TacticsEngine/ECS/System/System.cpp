//
//  System.cpp
//  TacticsEngine
//
//  Created by Curtis Covington on 1/27/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#include "System.h"
#include "SystemManager.h"

#include "EntityManager.h"
namespace TacticsEngine {
    System::System() : m_manager(nullptr), m_isRunning(true) {}
    
    System::~System() {
        
    }
    
    EntityManager* System::getEntityManager() {
        return m_manager->getEntityManager();
    }
}