#include "Light.hpp"

#include "Game.hpp"

extern Game *game;

using namespace std;
using namespace glm;

Light::Light(const char* vertexFilePath, const char* fragmentFilePath) :
    Model(vertexFilePath, fragmentFilePath)
{
    /* --- generate buffers ---*/
    glGenVertexArrays(1, &lightVAO);
    glGenBuffers(1, &lightVBO);
    
    /* --- bind buffers ---*/
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
    
    /* --- make object --- */
    ShapeData<SimpleVertex> light = ShapeGenerator::makeLight();
    numVertices = light.numVertices;
    
    /* --- bind data --- */
    glBufferData(GL_ARRAY_BUFFER, light.vertexBufferSize(), light.vertices, GL_DYNAMIC_DRAW);
    
    /* --- setGeometry --- */
    GLint positionAttrib = glGetAttribLocation(shader.getProgram(), "position"); // 0
    glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE, light.getStride(), light.getOffsetPointer(3, 0));
    glEnableVertexAttribArray(positionAttrib);
    
    GLint colorAttrib = glGetAttribLocation(shader.getProgram(), "lightObjectColor"); // 1
    glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, light.getStride(), light.getOffsetPointer(3, 1));
    glEnableVertexAttribArray(colorAttrib);
    
    /* --- free recources --- */
    light.clean();
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
};

void Light::render() const {
    shader.use();
    
    glm::mat4 fullMatrix, model, view, projection;
    
    /* --- model to view --- */
    model = glm::translate(model, game->lightPosition);
    model = glm::scale(model, glm::vec3(0.2f));
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f));

    /* --- world to view --- */
    view = game->getCamera()->GetViewMatrix();

    /* --- view to clip space --- */
    projection = game->getCamera()->GetProjection();
    
    /* use uniform matrix transformation */
    fullMatrix = projection * view * model;
    glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "fullMatrix"), 1, GL_FALSE, &fullMatrix[0][0]);
    
    /* Draw light object */
    glBindVertexArray(lightVAO);
    glDrawArrays(GL_TRIANGLES, 0, numVertices);
    glBindVertexArray(0);
}

void Light::clear() const {
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &lightVBO);
}
