#include "Triangle.hpp"

Triangle::Triangle(GLint verticesSize, GLfloat * vertices, GLsizei verticesQty, GLchar * vertexPath, GLchar * fragmentPath) :
    verticesSize(verticesSize),
    vertices(vertices),
    verticesQty(verticesQty),
    shader(ShaderLoader(vertexPath, fragmentPath))
{
    bindVBO();
    bindVAO();
    setAttributesPointers();
    loadTexture("resources/textures/container.jpg", &texture1);
    loadTexture("resources/textures/awesomeface.png", &texture2);
    unbind();
    
    camera.pos = glm::vec3(0.0f, 0.0f,  3.0f);
    camera.front = glm::vec3(0.0f, 0.0f, -1.0f);
    camera.up = glm::vec3(0.0f, 1.0f,  0.0f);
}

void Triangle::bindVBO()
{
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

void Triangle::bindVAO()
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
}


void Triangle::setAttributesPointers()
{
    GLint stride = 5 * sizeof(GLfloat);
    
    // position
    GLint positionAttrib = glGetAttribLocation(shader.getProgram(), "position"); // 0
    glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)0);
    glEnableVertexAttribArray(positionAttrib);

    // texture
    GLint textureAttrib = glGetAttribLocation(shader.getProgram(), "texCoord"); // 1
    glVertexAttribPointer(textureAttrib, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(textureAttrib);
    
}

void Triangle::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Triangle::loadTexture(char * texturePath, GLuint * texture)
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

void Triangle::cameraCallback(int key, int scancode, int action, int mode)
{
//GLfloat cameraSpeed = 0.05f;
//    if(key == GLFW_KEY_W) {
//        camera.pos += cameraSpeed * camera.front;
//    }
//    if(key == GLFW_KEY_S) {
//        camera.pos -= cameraSpeed * camera.front;
//    }
//    if(key == GLFW_KEY_A) {
//        camera.pos -= glm::normalize(glm::cross(camera.front, camera.up)) * cameraSpeed;
//    }
//    if(key == GLFW_KEY_D) {
//        camera.pos += glm::normalize(glm::cross(camera.front, camera.up)) * cameraSpeed;
//    }
};

void Triangle::movement(float deltaTime)
{
    GLfloat cameraSpeed = 5.0f * deltaTime;
    if (keyInput->keys[GLFW_KEY_W]) {
        camera.pos += cameraSpeed * camera.front;
    }
    
    if (keyInput->keys[GLFW_KEY_S]) {
        camera.pos -= cameraSpeed * camera.front;
    }
    
    if (keyInput->keys[GLFW_KEY_A]) {
        camera.pos -= glm::normalize(glm::cross(camera.front, camera.up)) * cameraSpeed;
    }
    
    if (keyInput->keys[GLFW_KEY_D]) {
        camera.pos += glm::normalize(glm::cross(camera.front, camera.up)) * cameraSpeed;
    }
}

void Triangle::transformationRender(glm::vec3 * cubePositions, GLint cubesSize)
{
    glm::mat4 model;
    glm::mat4 projection;
    glm::mat4 view = glm::lookAt(camera.pos, camera.pos + camera.front, camera.up);

    
    GLuint modelLoc = glGetUniformLocation(shader.getProgram(), "model");
    GLuint viewLoc = glGetUniformLocation(shader.getProgram(), "view");
    GLuint projectionLoc = glGetUniformLocation(shader.getProgram(), "projection");
    
    projection = glm::perspective(45.0f, (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);
    
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(VAO);
    if (cubePositions != nullptr) {
        GLfloat time = (GLfloat)glfwGetTime();
        for (GLuint i = 0; i < cubesSize; i++) {
            glm::mat4 model;
            model = glm::translate(model, cubePositions[i]);
            GLfloat angle = time * 20.0f * (i + 1);
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, verticesQty);
        }
    } else {
        model = glm::rotate(model, glm::radians((GLfloat)glfwGetTime() * 30.0f), glm::vec3(1.0f, 0.5f, 0.0f));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, verticesQty);
    }
    
    glBindVertexArray(0);
}

void Triangle::render(glm::vec3 * cubePositions, GLint cubesSize)
{
    shader.use();

    // bind textures
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glUniform1i(glGetUniformLocation(shader.getProgram(), "ourTexture1"), 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glUniform1i(glGetUniformLocation(shader.getProgram(), "ourTexture2"), 1);
    
    transformationRender(cubePositions, cubesSize);
    
    glBindVertexArray(0);
}

void Triangle::clear()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
