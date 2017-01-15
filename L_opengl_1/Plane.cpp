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
    
    /* --- make object --- */
    ShapeData<RegularVertex> plane = ShapeGenerator::makePlane();
    numVertices = plane.numVertices;
    
    /* --- buffer data --- */
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
    
    /* --- clean --- */
    plane.clean();
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Plane::render() const
{
    shader.use();

    /* --- bind ligth --- */
    GLint lightColorLoc  = glGetUniformLocation(shader.getProgram(), "lightColor");
    GLint ambientStrengthLoc = glGetUniformLocation(shader.getProgram(), "ambientStrength");
    glUniform3f(lightColorLoc,  1.0f, 1.0f, 1.0f);
    glUniform1f(ambientStrengthLoc, 0.1f);
    
    /* --- bind light position --- */
    GLint lightPositionLoc = glGetUniformLocation(shader.getProgram(), "lightPos");
    glUniform3f(lightPositionLoc, game->lightPosition.x, game->lightPosition.y, game->lightPosition.z);
    
    /* --- define transformation matrix --- */
    glm::mat4 fullMatrix, model, view, projection;
    
    /* --- model to view, send it to shader --- */
    model = glm::translate(model, game->lightPosition);
    model = glm::scale(model, glm::vec3(0.2f));
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "model"), 1, GL_FALSE, &model[0][0]);
    
    /* --- world to view --- */
    view = game->getCamera()->GetViewMatrix();
    
    /* --- view to clip space --- */
    projection = game->getCamera()->GetProjection();
    
    /* use uniform matrix transformation */
    fullMatrix = projection * view * model;
    glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "fullMatrix"), 1, GL_FALSE, &fullMatrix[0][0]);
    
    /* Draw light object */
    glBindVertexArray(planeVAO);
    glDrawArrays(GL_TRIANGLES, 0, numVertices);
    glBindVertexArray(0);
}

void Plane::clear() const
{
    glDeleteVertexArrays(1, &planeVAO);
    glDeleteBuffers(1, &planeVBO);
}
