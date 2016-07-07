//
//  PhysicsSystem.h
//  TacticsEngine
//
//  Created by Curtis Covington on 2/1/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#ifndef PhysicsSystem_h
#define PhysicsSystem_h

#include "System.h"
#include <vector>
#include <glm/vec2.hpp>
#include "CollisionComponent.h"

namespace TacticsEngine {
    enum class CollisionType {
        WORLD_BORDER,
        ENTITY,
    };
    struct Collision {
        CollisionType type;
        CollisionComponent* c{nullptr};
        glm::vec2 pos;
        Entity* e;
        Collision(CollisionType type, Entity* e) : type(type), e(e) {};
        Collision(CollisionType type, glm::vec2 pos) : type(type), pos(pos) {};
    };
    struct CollisionList {
        glm::vec2 pos;
        Entity* e;
        std::vector<Collision> collisions;
        
        bool hasCollisions() const { return collisions.size() > 0; };
    };
    
    class PhysicsSystem : public System {
    public:
        const float TIME_STEP = 0.20f;
        
        void init() override;
        void update(float dt) override;
        void step(float ts);
        void applyForce(Entity* e, const glm::vec2& force);
        void handleCollisions(const CollisionList& list);
        void handleCollision(Entity* e, const glm::vec2& pos, const Collision& collision);
        CollisionList getCollisions(const glm::vec2& pos, Entity* e);
        bool isColliding(const float a1, const float b1, const float a2, const float b2) const;
    private:
        
    };
}

#endif /* PhysicsSystem_h */
