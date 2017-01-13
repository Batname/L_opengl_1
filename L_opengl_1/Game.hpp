#ifndef Game_hpp
#define Game_hpp

#include "includes.h"

#include "callbacks.hpp"

#include "Frame.hpp"
#include "Cube.hpp"
#include "Light.hpp"

#include "Camera.hpp"


class Game
{
public:
    Game();
    
    int render();
    
    // getters
    GLFWwindow * getWindow();
    Camera* getCamera();
    
    // static const
    static const vec3 lightPosition;
    
private:
    int SCREEN_WIDTH, SCREEN_HEIGHT;

    GLFWwindow * window;
    Cube* cube;
    Light* light;
    Frame* frame;
    Camera* camera;
};

#endif /* Game_hpp */
