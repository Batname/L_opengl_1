#ifndef Cube_hpp
#define Cube_hpp

#include "ShaderLoader.hpp"

#include "includes.h"

struct Camera {
    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 up;
};

class Cube
{
public:
    Cube(GLint verticesSize, GLfloat * vertices, GLsizei verticesQty, GLchar * vertexPath, GLchar * fragmentPath);
    
    // public member
    void cameraCallback(int key, int scancode, int action, int mode);
    void mouseCallback(GLFWwindow* window, double xpos, double ypos);
    void clear();
    void render(glm::vec3 * cubePositions, GLint cubesSize);
    void movement(float deltaTime);

protected:
private:
    GLint verticesSize;
    GLfloat * vertices;
    GLsizei verticesQty;
    ShaderLoader shader;
    GLuint VBO, VAO, texture1, texture2;
    Camera camera;
    bool firstMouse;
    GLfloat yaw;
    GLfloat pitch;
    GLfloat lastX;
    GLfloat lastY;
    
    // private member
    void loadTexture(char * texturePath, GLuint * texture);
};

#endif /* Cube_hpp */
