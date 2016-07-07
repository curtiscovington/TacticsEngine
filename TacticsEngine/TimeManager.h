//
//  TimeManager.h
//  TacticsEngine
//
//  Created by Curtis Covington on 1/25/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#ifndef TimeManager_h
#define TimeManager_h

#include <chrono>

namespace TacticsEngine {
    using Clock = std::chrono::high_resolution_clock;
    using milliseconds = std::chrono::milliseconds;
    
    class TimeManager {
    public:
        TimeManager();
        ~TimeManager();
        float timeSinceLast();
        float now();
        
    private:
        std::chrono::time_point<Clock> _start;
        std::chrono::time_point<Clock> _prev;
        std::chrono::time_point<Clock> _curr;
    };
}


#endif /* TimeManager_h */
