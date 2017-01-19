#ifndef Game_hpp
#define Game_hpp

#include "callbacks.hpp"
#include "Frame.hpp"
#include "Cube.hpp"
#include "Light.hpp"
#include "Plane.hpp"
#include "Camera.hpp"

#include "ModelLoader.hpp"

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
    Plane* plane;

    Frame* frame;
    Camera* camera;
    
    ModelLoader* crisisModel;
};

#endif /* Game_hpp */
