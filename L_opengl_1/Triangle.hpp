#ifndef Triangle_hpp
#define Triangle_hpp


#include "ShaderLoader.hpp"

#include "includes.h"

class Triangle
{
public:
    Triangle(GLint verticesSize, GLfloat * vertices, GLchar * vertexPath, GLchar * fragmentPath);
    
    void render();
protected:
private:
    GLint verticesSize;
    GLfloat * vertices;
    ShaderLoader shader;
    
};

#endif /* Triangle_hpp */
