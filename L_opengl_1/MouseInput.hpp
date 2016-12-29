#ifndef MouseInput_hpp
#define MouseInput_hpp

#include "includes.h"
#include "Input.hpp"

using namespace std;


class MouseInput : public Input
{
    typedef function<void (GLFWwindow* window, double xpos, double ypos)> MouseCallback;
public:
    MouseInput(GLFWwindow *window);
    
    void addListener(MouseCallback cb);
    void emitEvent(GLFWwindow* window, double xpos, double ypos);
    
private:
    vector<MouseCallback> callbacks;
};

#endif /* MouseInput_hpp */
