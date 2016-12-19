#include "includes.h"
#include "basic_vertices.h"
#include "Triangle.hpp"

#include "KeyInput.hpp"
#include "Frame.hpp"

using namespace std;
using namespace std::placeholders;

int SCREEN_WIDTH, SCREEN_HEIGHT;

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void mainInputKeybordCallback(int key, int scancode, int action, int mode);

KeyInput *keyInput;
GLFWwindow *window;

int main(int argc, const char * argv[]) {

    // init glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RELEASE, GL_FALSE);

    // init window
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGS", nullptr, nullptr);
    if (window == nullptr) {
        cout << "Failed to create window"  << endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }
    
    // init glew
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        cout << "Failed to inin glew with experemental"  << endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }
    
    // init viewpoint
    glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    
    // openGl options
    glEnable(GL_DEPTH_TEST);
    
    
    // init custom Triangle
    Triangle triangle(sizeof(basic_vertices), basic_vertices, 36, "resources/shaders/core.vs", "resources/shaders/core.frag");
    
    // init frame
    Frame frame;
    
    // init user input
    keyInput = new KeyInput(window);
    keyInput->addListener(mainInputKeybordCallback);
    keyInput->addListener(bind(&Triangle::cameraCallback, &triangle, _1, _2, _3, _4));
    glfwSetKeyCallback(window, keyCallback);
    
    // game loop
    while (!glfwWindowShouldClose(window)) {
        frame.calculateFrame();
        
        // check evants
        glfwPollEvents();
        triangle.movement(frame.getDeltaTime());
        
        // clear
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // draw
        triangle.render(basic_cubePositions, (sizeof(basic_cubePositions) / sizeof(GLfloat) / 3));
        
        glfwSwapBuffers(window);
    }

    // reallocate
    triangle.clear();
    
    // success exit
    glfwTerminate();
    return EXIT_SUCCESS;
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            keyInput->keys[key] = true;
        } else if (action == GLFW_RELEASE) {
            keyInput->keys[key] = false;
        }
    }

    keyInput->emitEvent(key, scancode, action, mode);
}

void mainInputKeybordCallback(int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}


