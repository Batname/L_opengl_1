#ifndef callbacks_hpp
#define callbacks_hpp

#include "includes.h"
#include "Camera.hpp"

void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

#endif /* callbacks_hpp */
