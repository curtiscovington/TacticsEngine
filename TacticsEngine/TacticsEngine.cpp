//
//  TacticsEngine.cpp
//  TacticsEngine
//
//  Created by Curtis Covington on 1/23/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#include "TacticsEngine.h"
#include "Error.h"
#include <cstdlib>
#include <OpenGL/gl3.h>
#include "Vertex.h"
#include "Component.h"


namespace TacticsEngine {
    
    Core::Core() : _entityManager(new EntityManager()), _inputManager(new InputManager()) {
        _inputProcessor = std::unique_ptr<InputProcessor>(new InputProcessorSDL(_inputManager.get()));
    }
    
    Core::~Core() {
    
    }
    
    void Core::quit() {
        _isRunning = false;
    }
    
    void Core::init(int width, int height) {
        if (0 != SDL_Init(SDL_INIT_VIDEO)) {
            //fprintf(stderr, "\nUnable to initialize SDL: %s\n", SDL_GetError());
            Error::getInstance().fail(ErrorCodes::UNKNOWN);
        }
        
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        
        m_camera.init(width, height);
        
        //_entityManager->getSystemManager()->addSystem<PhysicsSystem>(Component::getComponentBitmask<PositionComponent, PhysicsComponent, CollisionComponent>())->init();
        
        _entityManager->getSystemManager()->addSystem<RenderSystem>(Component::getComponentBitmask<TextureComponent, PositionComponent>())->init(&m_camera);
        
//        _entityManager->getSystemManager();
        
        onInit();
        
        loop();
    }
    
    void Core::limitFPS() {
        static float targetFPS = 1.0f / _maxFPS;
        
        float elapsed = _timer.now() - _frameStartTime;
        std::printf("%lf\n", elapsed);
        float k = targetFPS - elapsed;
        while (k > 0) {
            elapsed = _timer.now() - _frameStartTime;
            k = targetFPS - elapsed;
        }
    }
    
    void Core::calculateFPS(float dt) {
        static int frame = 0;
        static float frameTimes[100];
        static float fps = 0.0f;
        frameTimes[frame++] = dt;
        if (frame >= 100) {
            float c = 0;
            for (int i = 0; i < 100; i++) {
                c += frameTimes[i];
            }
            
            fps = (1.0f / (c / 100.0f));
            
            frame = 0;
            std::printf("%lf\n", fps);
        }
    }
    
    void Core::loop() {
        
        
        while (_isRunning) {
            
            _frameStartTime = _timer.now();
           //
            float dt = _timer.timeSinceLast();

            _inputProcessor->process();
            if (_inputManager->isPressed(KeyCode::QUIT)) {
                quit();
            } else {
                update(dt);
            }
            _entityManager->update();
            _entityManager->getSystemManager()->update(dt);
            draw(dt);
            
            calculateFPS(dt);
            
            //limitFPS();
            
        }
    }
    
    void Core::draw(float dt) {
        
    }
    
}