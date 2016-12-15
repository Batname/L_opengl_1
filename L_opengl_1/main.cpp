#include "includes.h"
#include "KeyInput.hpp"
using namespace std;

int SCREEN_WIDTH, SCREEN_HEIGHT;

int main(int argc, const char * argv[]) {

    // init glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RELEASE, GL_FALSE);

    // init window
    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGS", nullptr, nullptr);
    if (window == nullptr) {
        cout << "Failed to create window"  << endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }
    
    // init user input
    KeyInput keyInput(window);
    keyInput.registerAll();
    
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
    
    // game loop
    while (!glfwWindowShouldClose(window)) {
        // check evants
        glfwPollEvents();
        
        // render here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glfwSwapBuffers(window);
    }

    // success exit
    glfwTerminate();
    return EXIT_SUCCESS;
}
