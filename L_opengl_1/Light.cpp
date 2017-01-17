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
    glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE, light.getStride(), (GLvoid*)0);
    glEnableVertexAttribArray(positionAttrib);
    
    GLint colorAttrib = glGetAttribLocation(shader.getProgram(), "lightObjectColor"); // 1
    glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, light.getStride(), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(colorAttrib);
    
    /* --- load objects --- */
    lightObjects = ShapeGenerator::getLights();
    
    /* --- free recources --- */
    light.clean();
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
};

void Light::draw() const
{
    glBindVertexArray(lightVAO);
    glDrawArrays(GL_TRIANGLES, 0, numVertices);
    glBindVertexArray(0);
}

void Light::render() const {
    shader.use();
    
    glm::mat4 view, projection;

    /* --- world to view --- */
    view = game->getCamera()->GetViewMatrix();

    /* --- view to clip space --- */
    projection = game->getCamera()->GetProjection();
    
    for(unsigned int i = 0; i < lightObjects.size; i++) {
        glm::mat4 fullMatrix, model;
        
        /* --- model to view --- */
        model = glm::translate(model, lightObjects.positions[i]);
        model = glm::scale(model, glm::vec3(0.2f));
        model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f));
        
        /* use uniform matrix transformation */
        fullMatrix = projection * view * model;
        glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "fullMatrix"), 1, GL_FALSE, &fullMatrix[0][0]);
        
        /* Draw light object */
        draw();
    }
}

void Light::clear() {
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &lightVBO);
    lightObjects.clean();
}
