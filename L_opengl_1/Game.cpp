#include "Game.hpp"

using namespace std;
using namespace std::placeholders;
using namespace glm;

const vec3 Game::lightPosition = vec3(1.2f, 1.0f, 2.0f);

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
    
    /* --- init models --- */
    cube = new Cube("resources/shaders/cube.vs", "resources/shaders/cube.frag");
    light = new Light("resources/shaders/light.vs", "resources/shaders/light.frag");
    plane = new Plane("resources/shaders/plane.vs", "resources/shaders/plane.frag");
    
    /* --- init crisis model --- */
    crisisModel = new ModelLoader("resources/models/nanosuit.obj", "resources/shaders/modelLoading.vs", "resources/shaders/modelLoading.frag");
    
    /* --- TEST CODE --- */
    ourModel = new Model1("resources/models/nanosuit.obj");
    
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
    
    ShaderLoader shader("resources/shaders/modelLoading.vs", "resources/shaders/modelLoading.frag");
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
        cube->render();
        light->render();
        plane->render();
        crisisModel->render();
        
        /* --- TEST CODE --- */
//        shader.use();

        
//        glm::mat4 model;
//        model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
//        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
//
//        /* --- world to view --- */
//        glm::mat4 view = camera->GetViewMatrix();
//        
//        /* --- view to clip space --- */
//        glm::mat4 projection = camera->GetProjection();
//        
//        glm::mat4 fullMatrix = projection * view * model;
//        glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "fullMatrix"), 1, GL_FALSE, &fullMatrix[0][0]);
//
//        ourModel->Draw(shader);
        
        glfwSwapBuffers(window);
    }
    
    // reallocate
    cube->clear();
    light->clear();
    plane->clear();
    
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
