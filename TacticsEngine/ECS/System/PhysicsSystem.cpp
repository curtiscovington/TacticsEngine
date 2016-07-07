//
//  PhysicsSystem.cpp
//  TacticsEngine
//
//  Created by Curtis Covington on 2/2/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#include "PhysicsSystem.h"
#include <algorithm>
#include "Entity.h"
#include "Component.h"
#include <glm/vec2.hpp>
#include <memory>

namespace TacticsEngine {
    void PhysicsSystem::init() {
        
    }
    void PhysicsSystem::update(float dt) {
        // Implement a fixed timestep
        float total = 0.0f;
        while (total < dt) {
            float ts = std::min(dt-total, TIME_STEP);
            step(ts);
            total += ts;
        }
    }
    
    void PhysicsSystem::step(float ts) {
        for (int i = 0; i < m_entities.size(); i++) {
            PhysicsComponent* phys = m_entities[i]->getComponent<PhysicsComponent>();
            PositionComponent* pos = m_entities[i]->getComponent<PositionComponent>();
            applyForce(m_entities[i], 5.0f * glm::vec2(0, -1.0f) * ts);
//            phys->velocity += glm::vec2(0, -0.1f) * ts;
            if (!phys->isStatic) {
                if (m_entities[i]->hasComponent(Component::getComponentBitmask<CollisionComponent>())) {
                    glm::vec2 newPos = pos->pos + phys->velocity;
                    handleCollisions(getCollisions(newPos, m_entities[i]));
                } else {
                    pos->pos += phys->velocity * ts;
                }
            }
        }
    }
    
    void PhysicsSystem::applyForce(Entity* e, const glm::vec2& force) {
        if (!e->getComponent<PhysicsComponent>()->isStatic) {
            e->getComponent<PhysicsComponent>()->velocity += force;
        }
    }
    
    void PhysicsSystem::handleCollisions(const CollisionList& list) {
        if (list.hasCollisions()) {
            for (int i = 0; i < list.collisions.size(); i++) {
                handleCollision(list.e, list.pos, list.collisions[i]);
            }
        } else {
            list.e->getComponent<PositionComponent>()->pos = list.pos;
        }
    }
    
    void PhysicsSystem::handleCollision(Entity* e, const glm::vec2& pos, const Collision& collision) {
        switch (collision.type) {
            case CollisionType::WORLD_BORDER:
                
                //e->getComponent<PositionComponent>()->pos = pos - collision.pos;
                //e->getComponent<PhysicsComponent>()->velocity -= e->getComponent<PhysicsComponent>()->velocity * 0.04f;
                //e->getComponent<PhysicsComponent>()->velocity = -0.9f * e->getComponent<PhysicsComponent>()->velocity;
                
                break;
            case CollisionType::ENTITY:
               
                e->getComponent<PositionComponent>()->pos -= collision.pos;
                e->getComponent<PhysicsComponent>()->velocity = glm::vec2(0,0);
               // e->getComponent<PhysicsComponent>()->velocity = e->getComponent<PhysicsComponent>()->velocity * 0.5f;
               // e->getComponent<PhysicsComponent>()->velocity = -0.5f * e->getComponent<PhysicsComponent>()->velocity;
                
                //collision.e->getComponent<PositionComponent>()->pos = pos - collision.pos;
                //e->getComponent<PhysicsComponent>()->velocity -= e->getComponent<PhysicsComponent>()->velocity * 0.04f;
                //collision.e->getComponent<PhysicsComponent>()->velocity = -0.5f * e->getComponent<PhysicsComponent>()->velocity;
                break;
            default:
                break;
        }
    }
    
    // This needs to be refactored out into a collision system
    CollisionList PhysicsSystem::getCollisions(const glm::vec2& pos, Entity* e) {
        CollisionList list;
        list.e = e;
        list.pos = pos;
        CollisionComponent* c = e->getComponent<CollisionComponent>();
//        if (c->isRect()) {
//            float x = 0;
//            float y = 0;
//            
//            if (pos.x - c->rect.width/2 < -1.0) {
//                x = (pos.x - c->rect.width/2) + 1;
//                list.collisions.emplace_back(CollisionType::WORLD_BORDER, glm::vec2(x, y) );
//            } else if (pos.x + c->rect.width/2 > 1.0) {
//                x = (pos.x + c->rect.width/2) - 1;
//                list.collisions.emplace_back(CollisionType::WORLD_BORDER, glm::vec2(x, y) );
//            }
//            if (pos.y - c->rect.height/2 < -1.0) {
//                y = (pos.y - c->rect.height/2) + 1;
//                list.collisions.emplace_back(CollisionType::WORLD_BORDER, glm::vec2(x, y) );
//            } else if (pos.y + c->rect.width/2 > 1.0) {
//                y = (pos.y + c->rect.height/2) - 1;
//                list.collisions.emplace_back(CollisionType::WORLD_BORDER, glm::vec2(x, y) );
//            }
//            
//            if (x > 0 || y > 0) {
//                
//            }
//            
//        } else {
//            
//        }
        
        for (int i = 0; i < m_entities.size(); i++) {
            if (e->getID() != m_entities[i]->getID()) {
                float left = pos.x - e->getComponent<CollisionComponent>()->rect.width/2;
                // Right
                float right = pos.x + e->getComponent<CollisionComponent>()->rect.width/2;
                if (isColliding(right,
                   m_entities[i]->getComponent<PositionComponent>()->pos.x - m_entities[i]->getComponent<CollisionComponent>()->rect.width/2 ,
                                right,
                                m_entities[i]->getComponent<PositionComponent>()->pos.x +m_entities[i]->getComponent<CollisionComponent>()->rect.width/2 ))
                {
                    if (isColliding(pos.y - e->getComponent<CollisionComponent>()->rect.height/2,
                                    m_entities[i]->getComponent<PositionComponent>()->pos.y - m_entities[i]->getComponent<CollisionComponent>()->rect.height/2 ,
                                    pos.y - e->getComponent<CollisionComponent>()->rect.height/2,
                                    m_entities[i]->getComponent<PositionComponent>()->pos.y + m_entities[i]->getComponent<CollisionComponent>()->rect.height/2 ))
                    {
                       list.collisions.emplace_back(CollisionType::ENTITY,e);
                    }
                    else if (isColliding(pos.y + e->getComponent<CollisionComponent>()->rect.height/2,
                                    m_entities[i]->getComponent<PositionComponent>()->pos.y - m_entities[i]->getComponent<CollisionComponent>()->rect.height/2 ,
                                    pos.y + e->getComponent<CollisionComponent>()->rect.height/2,
                                    m_entities[i]->getComponent<PositionComponent>()->pos.y + m_entities[i]->getComponent<CollisionComponent>()->rect.height/2 ))
                    {
                        list.collisions.emplace_back(CollisionType::ENTITY,e);
                    }
                }
                
                else if (isColliding(left,
                                     m_entities[i]->getComponent<PositionComponent>()->pos.x - m_entities[i]->getComponent<CollisionComponent>()->rect.width/2 ,
                                     left,
                                     m_entities[i]->getComponent<PositionComponent>()->pos.x +m_entities[i]->getComponent<CollisionComponent>()->rect.width/2 ))
                {
                    if (isColliding(pos.y - e->getComponent<CollisionComponent>()->rect.height/2,
                                    m_entities[i]->getComponent<PositionComponent>()->pos.y - m_entities[i]->getComponent<CollisionComponent>()->rect.height/2 ,
                                    pos.y - e->getComponent<CollisionComponent>()->rect.height/2,
                                    m_entities[i]->getComponent<PositionComponent>()->pos.y + m_entities[i]->getComponent<CollisionComponent>()->rect.height/2 ))
                    {
                        list.collisions.emplace_back(CollisionType::ENTITY,e);
                    }
                    else if (isColliding(pos.y + e->getComponent<CollisionComponent>()->rect.height/2,
                                         m_entities[i]->getComponent<PositionComponent>()->pos.y - m_entities[i]->getComponent<CollisionComponent>()->rect.height/2 ,
                                         pos.y + e->getComponent<CollisionComponent>()->rect.height/2,
                                         m_entities[i]->getComponent<PositionComponent>()->pos.y + m_entities[i]->getComponent<CollisionComponent>()->rect.height/2 ))
                    {
                        list.collisions.emplace_back(CollisionType::ENTITY,e);
                    }
                }
            }
            
            
        }
        
        return list;
    }
    bool PhysicsSystem::isColliding(const float a1, const float b1, const float a2, const float b2) const {
        return (a1 >= b1 && a2 <= b2);
    }
    
    
}
