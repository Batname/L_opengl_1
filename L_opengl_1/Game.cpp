#include "Game.hpp"
#include "basic_vertices.h"

using namespace std;
using namespace std::placeholders;

Game::Game()
{
    // init glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RELEASE, GL_FALSE);
    
    // init window
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OpenGS", nullptr, nullptr);
    if (window == nullptr) {
        cout << "Failed to create window"  << endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    // glfw options
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // init glew
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        cout << "Failed to inin glew with experemental"  << endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    // init viewpoint
    glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    
    // openGl options
    glEnable(GL_DEPTH_TEST);
    
    // init custom Cube
    cube = new Cube(sizeof(basic_vertices), basic_vertices, 36, "resources/shaders/cube.vs", "resources/shaders/cube.frag");
    
    // init light
    light = new Light();
    
    // init camera
    camera = new Camera(vec3(0.0f, 0.0f, 3.0f));
    
    // init frame
    frame = new Frame;
    
    // init user input
    glfwSetKeyCallback(window, keyCallback);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);

}

int Game::render()
{
    // game loop
    while (!glfwWindowShouldClose(window)) {
        frame->calculateFrame();
        
        // check evants
        glfwPollEvents();
        camera->DoMovement(frame->getDeltaTime());
        
        // clear
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // draw
        cube->render(basic_cubePositions, (sizeof(basic_cubePositions) / sizeof(GLfloat) / 3));
        
        light->render();
        
        glfwSwapBuffers(window);
    }
    
    // reallocate
    cube->clear();
    
    // success exit
    glfwTerminate();
    return EXIT_SUCCESS;
}

GLFWwindow * Game::getWindow()
{
    return window;
}

Camera* Game::getCamera() {
    return camera;
}
