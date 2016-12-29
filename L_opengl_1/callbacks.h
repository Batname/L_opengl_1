#ifndef callbacks_h
#define callbacks_h

#include "includes.h"

#include "MouseInput.hpp"
#include "KeyInput.hpp"

extern MouseInput *mouseInput;
extern KeyInput *keyInput;
extern GLFWwindow *window;

void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    mouseInput->emitEvent(window, xpos, ypos);
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
        return;
    }
    
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            keyInput->keys[key] = true;
        } else if (action == GLFW_RELEASE) {
            keyInput->keys[key] = false;
        }
    }
    
    keyInput->emitEvent(key, scancode, action, mode);
}

#endif /* callbacks_h */
