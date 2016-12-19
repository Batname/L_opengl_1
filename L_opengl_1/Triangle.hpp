#ifndef Triangle_hpp
#define Triangle_hpp


#include "ShaderLoader.hpp"

#include "includes.h"
#include "KeyInput.hpp"

extern KeyInput *keyInput;

struct Camera {
    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 up;
};

class Triangle
{
public:
    Triangle(GLint verticesSize, GLfloat * vertices, GLsizei verticesQty, GLchar * vertexPath, GLchar * fragmentPath);
    
    // public member
    void cameraCallback(int key, int scancode, int action, int mode);
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
    
    // private member
    void loadTexture(char * texturePath, GLuint * texture);
};

#endif /* Triangle_hpp */
