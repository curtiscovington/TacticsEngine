//
//  TimeManager.cpp
//  TacticsEngine
//
//  Created by Curtis Covington on 1/25/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#include "TimeManager.h"

namespace TacticsEngine {
    TimeManager::TimeManager() : _start(Clock::now()) {
        _prev = _start;
        _curr = _start;
    }
    
    TimeManager::~TimeManager() {
        
    }
    
    float TimeManager::timeSinceLast() {
        _prev = _curr;
        _curr = Clock::now();
        std::chrono::duration<float> t = (_curr - _prev);
        return t.count();
    }
    
    float TimeManager::now() {
        auto now = Clock::now();
        
        std::chrono::duration<float> t = now.time_since_epoch();
        
        return t.count();
    }
}