#include "callbacks.hpp"
#include "Game.hpp"

extern Game * game;

void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    game->getMouseInput()->emitEvent(window, xpos, ypos);
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
        return;
    }
    
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            game->getKeyInput()->keys[key] = true;
        } else if (action == GLFW_RELEASE) {
            game->getKeyInput()->keys[key] = false;
        }
    }
    
    game->getKeyInput()->emitEvent(key, scancode, action, mode);
}
