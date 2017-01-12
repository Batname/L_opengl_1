#ifndef Cube_hpp
#define Cube_hpp

#include "ShaderLoader.hpp"

#include "includes.h"

class Cube
{
public:
    Cube(GLint verticesSize, GLfloat * vertices, GLsizei verticesQty, GLchar * vertexPath, GLchar * fragmentPath);
    
    // public member
    void clear();
    void render(glm::vec3 * cubePositions, GLint cubesSize);

protected:
private:
    GLint verticesSize;
    GLfloat * vertices;
    GLsizei verticesQty;
    ShaderLoader shader;
    GLuint VBO, VAO, texture1, texture2;
    bool firstMouse;
    GLfloat yaw;
    GLfloat pitch;
    GLfloat lastX;
    GLfloat lastY;
    
    // private member
    void loadTexture(char * texturePath, GLuint * texture);
    void bindTextures();
    void bindLight();

};

#endif /* Cube_hpp */
