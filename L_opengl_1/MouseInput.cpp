#include "MouseInput.hpp"

MouseInput::MouseInput(GLFWwindow *window) :
    Input(window)
{
}

void MouseInput::addListener(MouseCallback cb)
{
    callbacks.push_back(cb);
}

void MouseInput::emitEvent(GLFWwindow* window, double xpos, double ypos)
{
    std::cout << "event emit" << std::endl;

    for(auto it : callbacks){
        it(window, xpos, ypos);
    }
}
