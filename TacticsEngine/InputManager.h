//
//  InputManager.h
//  TacticsEngine
//
//  Created by Curtis Covington on 1/24/16.
//  Copyright © 2016 Curtis Covington. All rights reserved.
//

#ifndef InputManager_h
#define InputManager_h

#include <unordered_map>

namespace TacticsEngine {
   
    struct MousePosition {
        MousePosition(int x, int y) : x(x), y(y) {};
        int x, y;
    };
    enum class KeyCode {
        UNKNOWN, QUIT,
        A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,
        NUM_1, NUM_2, NUM_3, NUM_4, NUM_5, NUM_6, NUM_7, NUM_8, NUM_9, NUM_0,
        MOUSE_LEFT, MOUSE_RIGHT,
        ARROW_LEFT, ARROW_RIGHT, ARROW_UP, ARROW_DOWN,
        SHIFT, SPACE
    };
    namespace Internal {
        // Allows us to hash the KeyCode
        struct KeyCodeHash {
            template <typename T> std::size_t operator()(T t) const { return static_cast<std::size_t>(t); }
        };
    }
    
    class InputManager {
    public:
        InputManager();
        ~InputManager();
        
        void press(const KeyCode& key);
        void release(const KeyCode& key);
        bool isPressed(const KeyCode& key);
        
        MousePosition getMousePosition() const;
        void setMousePosition(int x, int y);
    private:
        std::unordered_map<KeyCode, bool, Internal::KeyCodeHash> _keyMap;
        MousePosition _mousePosition;
    };

}
#endif /* InputManager_h */
