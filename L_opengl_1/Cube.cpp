#include "Cube.hpp"
#include "Game.hpp"
#include "constants.h"

extern Game *game;

Cube::Cube(GLint verticesSize, GLfloat * vertices, GLsizei verticesQty, GLchar * vertexPath, GLchar * fragmentPath) :
    verticesSize(verticesSize),
    vertices(vertices),
    verticesQty(verticesQty),
    shader(ShaderLoader(vertexPath, fragmentPath))
{
    /* --- bindVBO ---*/
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    /* --- bindVAO ---*/
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
    
    /* --- bindTexture ---*/
    GLint stride = 5 * sizeof(GLfloat);
    // position
    GLint positionAttrib = glGetAttribLocation(shader.getProgram(), "position"); // 0
    glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)0);
    glEnableVertexAttribArray(positionAttrib);
    
    // texture
    GLint textureAttrib = glGetAttribLocation(shader.getProgram(), "texCoord"); // 1
    glVertexAttribPointer(textureAttrib, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(textureAttrib);
    
    loadTexture("resources/textures/container.jpg", &texture1);
    loadTexture("resources/textures/awesomeface.png", &texture2);
    
    /* --- unbind ---*/
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    camera.pos = glm::vec3(0.0f, 0.0f, 3.0f);
    camera.front = glm::vec3(0.0f, 0.0f, -1.0f);
    camera.up = glm::vec3(0.0f, 1.0f,  0.0f);
    
    firstMouse = true;
    yaw   = -90.0f;
    pitch =   0.0f;
    lastX =  WINDOW_WIDTH  / 2.0;
    lastY =  WINDOW_HEIGHT / 2.0;
}

void Cube::loadTexture(char * texturePath, GLuint * texture)
{
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);
    
    // texture filters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // texture mipmaps
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // loan and generate mipmaps
    int width, height;
    unsigned char *image = SOIL_load_image(texturePath, &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    // clear
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Cube::cameraCallback(int key, int scancode, int action, int mode)
{

};

void Cube::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    
    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
    
    GLfloat sensitivity = 0.05;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    
    yaw   += xoffset;
    pitch += yoffset;
    
    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;
    
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    camera.front = glm::normalize(front);
};

void Cube::movement(float deltaTime)
{
    GLfloat cameraSpeed = 5.0f * deltaTime;
    if (game->getKeyInput()->keys[GLFW_KEY_W]) {
        camera.pos += cameraSpeed * camera.front;
    }
    
    if (game->getKeyInput()->keys[GLFW_KEY_S]) {
        camera.pos -= cameraSpeed * camera.front;
    }
    
    if (game->getKeyInput()->keys[GLFW_KEY_A]) {
        camera.pos -= glm::normalize(glm::cross(camera.front, camera.up)) * cameraSpeed;
    }
    
    if (game->getKeyInput()->keys[GLFW_KEY_D]) {
        camera.pos += glm::normalize(glm::cross(camera.front, camera.up)) * cameraSpeed;
    }
    
    if (game->getKeyInput()->keys[GLFW_KEY_R]) {
        camera.pos += cameraSpeed * camera.up;
    }
    
    if (game->getKeyInput()->keys[GLFW_KEY_F]) {
        camera.pos -= cameraSpeed * camera.up;
    }
}

void Cube::render(glm::vec3 * cubePositions, GLint cubesSize)
{
    glm::mat4 fullMatrix;
    // model to world
    glm::mat4 model(1.0f);
    // world to view
    glm::mat4 view = glm::lookAt(camera.pos, camera.pos + camera.front, camera.up);
    // view to clip space
    glm::mat4 projection = glm::perspective(45.0f, (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);
    
    shader.use();

    // bind textures
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glUniform1i(glGetUniformLocation(shader.getProgram(), "ourTexture1"), 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glUniform1i(glGetUniformLocation(shader.getProgram(), "ourTexture2"), 1);
    
    // draw
    glBindVertexArray(VAO);
    for (GLuint i = 0; i < cubesSize; i++) {
        // model to view
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        model = glm::translate(model, cubePositions[i]);
        model = glm::rotate(model, glm::radians(20.0f * (i + 1)), glm::vec3(1.0f, 0.3f, 0.5f));
        
        fullMatrix = projection * view * model;
        glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "fullMatrix"), 1, GL_FALSE, glm::value_ptr(fullMatrix));
        
        // draw and reset model
        glDrawArrays(GL_TRIANGLES, 0, verticesQty);
        model = glm::mat4(1.0f);
    }
    glBindVertexArray(0);
}

void Cube::clear()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}