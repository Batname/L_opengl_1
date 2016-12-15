#ifndef Triangle_hpp
#define Triangle_hpp


#include "ShaderLoader.hpp"

#include "includes.h"

class Triangle
{
public:
    Triangle(GLint verticesSize, GLfloat * vertices, GLsizei verticesQty, GLchar * vertexPath, GLchar * fragmentPath);
    Triangle(GLint verticesSize, GLfloat * vertices, GLint indicesSize, GLuint * indices, GLchar * vertexPath, GLchar * fragmentPath);
    
    void render();
    void clear();
protected:
private:
    GLint verticesSize;
    GLfloat * vertices;
    GLint indicesSize = 0;
    GLuint * indices = nullptr;
    
    GLsizei verticesQty;

    ShaderLoader shader;
    
    GLuint VBO, VAO, EBO;
    
    // methods
    void bindVBO();
    void bindVAO();
    void bindEBO();
    void setAttributesPointers();
    void unbind();
};

#endif /* Triangle_hpp */
