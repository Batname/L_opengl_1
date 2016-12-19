//
//  KeyInput.hpp
//  L_opengl_1
//
//  Created by apple on 2016-12-15.
//  Copyright © 2016 apple. All rights reserved.
//

#ifndef KeyInput_hpp
#define KeyInput_hpp

#include "includes.h"
#include "Input.hpp"

using namespace std;
using namespace std::placeholders;

class KeyInput : public Input
{
    typedef function<void (int key, int scancode, int action, int mode)> keyInputListener;
public:
    KeyInput(GLFWwindow *window);
    
    void addListener(keyInputListener listener);
    void emitEvent(int key, int scancode, int action, int mode);
    bool keys[1024] = {};
protected:
    
private:
    vector<keyInputListener> listeners;
};

#endif /* KeyInput_hpp */
