//
//  KeyInput.cpp
//  L_opengl_1
//
//  Created by apple on 2016-12-15.
//  Copyright © 2016 apple. All rights reserved.
//

#include "KeyInput.hpp"

KeyInput::KeyInput(GLFWwindow *window) :
    Input(window)
{
    glfwSetKeyCallback(window, keyCallback);
}

// typedef void (* GLFWkeyfun)(GLFWwindow*,int,int,int,int);
void KeyInput::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}
