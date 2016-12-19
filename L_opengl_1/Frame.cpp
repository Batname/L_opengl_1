
#include "Frame.hpp"

void Frame::calculateFrame()
{
    GLfloat currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

GLfloat Frame::getDeltaTime()
{
    return deltaTime;
}
