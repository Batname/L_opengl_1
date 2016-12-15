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

class KeyInput : public Input
{
public:
    KeyInput(GLFWwindow *window);
    
    void registerAll();
    
protected:
    
private:
    // methods
    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);

};

#endif /* KeyInput_hpp */
