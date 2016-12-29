#ifndef Game_hpp
#define Game_hpp

#include "includes.h"

#include "KeyInput.hpp"
#include "MouseInput.hpp"
#include "callbacks.hpp"

#include "Frame.hpp"
#include "Triangle.hpp"


class Game
{
public:
    Game();
    
    int render();
    
    // getters
    KeyInput * getKeyInput();
    MouseInput * getMouseInput();
    GLFWwindow * getWindow();
    
private:
    int SCREEN_WIDTH, SCREEN_HEIGHT;
    
    KeyInput * keyInput;
    MouseInput * mouseInput;
    GLFWwindow * window;
    Triangle * triangle;
    Frame * frame;
};

#endif /* Game_hpp */
