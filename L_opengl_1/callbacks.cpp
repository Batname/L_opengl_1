#include "callbacks.hpp"
#include "Game.hpp"

extern Game * game;

static bool firstMouse = true;
static GLfloat lastX = 400, lastY = 300;

void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    
    if(firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    
    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;
    
    lastX = xpos;
    lastY = ypos;
    
    game->getCamera()->ProcessMouseMovement(xoffset, yoffset);
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
        return;
    }
    
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            Camera::keys[key] = true;
        } else if (action == GLFW_RELEASE) {
            Camera::keys[key] = false;
        }
    }
    
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    game->getCamera()->ProcessMouseScroll(yoffset);
}
