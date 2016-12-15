#include "Triangle.hpp"

Triangle::Triangle(GLint verticesSize, GLfloat * vertices, GLchar * vertexPath, GLchar * fragmentPath) :
    verticesSize(verticesSize),
    vertices(vertices),
    shader(ShaderLoader(vertexPath, fragmentPath))
{

}

void Triangle::render()
{
}
