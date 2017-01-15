#include "Plane.hpp"
#include "Game.hpp"

extern Game *game;

using namespace std;
using namespace glm;

Plane::Plane(const char* vertexFilePath, const char* fragmentFilePath) :
    Model(vertexFilePath, fragmentFilePath)
{
    /* --- generate buffers --- */
    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);
    
    /* --- bind buffers --- */
    glBindVertexArray(planeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    
    /* --- buffer data --- */
    ShapeData<RegularVertex> plane = ShapeGenerator::makePlane();
    glBufferData(GL_ARRAY_BUFFER, plane.vertexBufferSize(), plane.vertices, GL_DYNAMIC_DRAW);
    
    /* --- setGeometry --- */
    GLint positionAttrib = glGetAttribLocation(shader.getProgram(), "position"); // 0
    glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE, plane.getStride(), (GLvoid*)0);
    glEnableVertexAttribArray(positionAttrib);
    
    GLint colorAttrib = glGetAttribLocation(shader.getProgram(), "color"); // 1
    glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, plane.getStride(), (GLvoid*)(sizeof(vec3)));
    glEnableVertexAttribArray(colorAttrib);
    
    GLint normalAttrib = glGetAttribLocation(shader.getProgram(), "normal"); // 2
    glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, GL_FALSE, plane.getStride(), (GLvoid*)(sizeof(vec3) * 2));
    glEnableVertexAttribArray(normalAttrib);
    
    cout << positionAttrib << endl;
    cout << colorAttrib << endl;
    cout << normalAttrib << endl;
    /* --- clean --- */
    plane.clean();
}

void Plane::render() const
{

}

void Plane::clear() const
{

}
