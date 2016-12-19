//
//  KeyInput.cpp
//  L_opengl_1
//
//  Created by apple on 2016-12-15.
//  Copyright © 2016 apple. All rights reserved.
//

#include "KeyInput.hpp"

using namespace std;

KeyInput::KeyInput(GLFWwindow *window) :
    Input(window)
{
}

void KeyInput::addListener(keyInputListener listener)
{
    listeners.push_back(listener);
}

void KeyInput::emitEvent(int key, int scancode, int action, int mode)
{
    for (vector<keyInputListener>::iterator it = listeners.begin(); it != listeners.end(); it++) {
        
        (*it)(key, scancode, action, mode);
    }
}
