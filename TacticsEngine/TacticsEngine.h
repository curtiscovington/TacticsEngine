//
//  TacticsEngine.h
//  TacticsEngine
//
//  Created by Curtis Covington on 1/23/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#ifndef TacticsEngine_h
#define TacticsEngine_h
#include <SDL2/SDL.h>
#include "glm/glm.hpp"

#include "InputManager.h"
#include "InputProcessorSDL.h"
#include <memory>
#include "TimeManager.h"
#include "GLSLProgram.h"
#include "EntityManager.h"
#include "SystemManager.h"
#include "Camera.h"

namespace TacticsEngine {
    constexpr int DEFAULT_SCREEN_WIDTH = 800;
    constexpr int DEFAULT_SCREEN_HEIGHT = 600;
    struct TextureComponent;
    enum class GameState {
        RUNNING,
    };
    
    class Core {
    public:
        Core();
        ~Core();
        virtual void init(int width = DEFAULT_SCREEN_WIDTH, int height = DEFAULT_SCREEN_HEIGHT) final;
        virtual void onInit() = 0;
        virtual void update(float dt) = 0;
        
        void quit();
    private:
        void loop();
        void draw(float dt);
        void limitFPS();
        void calculateFPS(float dt);
        
       
        std::unique_ptr<InputProcessor> _inputProcessor;
        bool _isRunning{true};
        float _frameStartTime;
    protected:
        Camera m_camera;
        
        TimeManager _timer;
        std::unique_ptr<InputManager> _inputManager;
        float _maxFPS{70.0f};
        GLSLProgram _glslProgram;
        
        Entity* _ent;
        EntityManager* _entityManager;
        
    };
    
}
#endif /* TacticsEngine_h */
