//
//  InputManager.cpp
//  TacticsEngine
//
//  Created by Curtis Covington on 1/24/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#include "InputManager.h"

namespace TacticsEngine {
    InputManager::InputManager() : _mousePosition(0,0) {
        
    }
    
    InputManager::~InputManager() {
        
    }
  
    
    void InputManager::press(const TacticsEngine::KeyCode &key) {
        _keyMap[key] = true;
    }
    
    void InputManager::release(const TacticsEngine::KeyCode &key) {
        auto it = _keyMap.find(key);
        if (it != _keyMap.end()) {
            _keyMap[key] = false;
        }
    }
    
    bool InputManager::isPressed(const TacticsEngine::KeyCode &key) {
        auto it = _keyMap.find(key);
        if (it != _keyMap.end()) {
            return it->second;
        }
        
        return false;
    }
    
    MousePosition InputManager::getMousePosition() const {
        return _mousePosition;
    }
    
    void InputManager::setMousePosition(int x, int y) {
        _mousePosition.x = x;
        _mousePosition.y = y;
    }
}