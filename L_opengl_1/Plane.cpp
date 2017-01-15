#include "Plane.hpp"
#include "Game.hpp"

extern Game *game;

using namespace std;
using namespace glm;

Plane::Plane(const char* vertexFilePath, const char* fragmentFilePath) :
    WorldModel(vertexFilePath, fragmentFilePath)
{
    /* --- generate buffers --- */
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    /* --- bind buffers --- */
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    /* --- make object --- */
    ShapeData<RegularVertex> plane = ShapeGenerator::makePlane();
    numVertices = WorldModel::numVertices = plane.numVertices;
    
    /* --- buffer data --- */
    glBufferData(GL_ARRAY_BUFFER, plane.vertexBufferSize(), plane.vertices, GL_DYNAMIC_DRAW);
    
    /* --- setGeometry --- */
    GLint positionAttrib = glGetAttribLocation(shader.getProgram(), "position"); // 0
    glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE, plane.getStride(), (GLvoid*)0);
    glEnableVertexAttribArray(positionAttrib);
    
    GLint colorAttrib = glGetAttribLocation(shader.getProgram(), "color"); // 1
    glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, plane.getStride(), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(colorAttrib);
    
    GLint normalAttrib = glGetAttribLocation(shader.getProgram(), "normal"); // 2
    glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, GL_FALSE, plane.getStride(), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(normalAttrib);
    
    /* --- clean --- */
    plane.clean();
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Plane::renderModel() const
{
//    /* --- define transformation matrix --- */
    glm::mat4 fullMatrix, model, view, projection;
    
    /* --- model to view, send it to shader --- */
    model = glm::translate(model, vec3(0.0f));
    model = glm::scale(model, glm::vec3(10.0f, 1.0f, 10.0f));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "model"), 1, GL_FALSE, &model[0][0]);
    
    /* --- world to view --- */
    view = game->getCamera()->GetViewMatrix();
    
    /* --- view to clip space --- */
    projection = game->getCamera()->GetProjection();
    
    /* use uniform matrix transformation */
    fullMatrix = projection * view * model;
    glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "fullMatrix"), 1, GL_FALSE, &fullMatrix[0][0]);
}

void Plane::render() const
{
    this->preRender();
    renderModel();
    this->renderLight();
    this->draw();
}

void Plane::clear() const
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
