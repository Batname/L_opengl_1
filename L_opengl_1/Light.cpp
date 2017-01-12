#include "Light.hpp"

#include "Game.hpp"

extern Game *game;

using namespace std;
using namespace glm;

const Light::Vertex Light::vertices[] = {
    vec3(-0.5f, -0.5f, -0.5f), vec3(1.0f),
    vec3( 0.5f, -0.5f, -0.5f), vec3(1.0f),
    vec3( 0.5f,  0.5f, -0.5f), vec3(1.0f),
    vec3( 0.5f,  0.5f, -0.5f), vec3(1.0f),
    vec3(-0.5f,  0.5f, -0.5f), vec3(1.0f),
    vec3(-0.5f, -0.5f, -0.5f), vec3(1.0f),
    
    vec3(-0.5f, -0.5f,  0.5f), vec3(1.0f),
    vec3( 0.5f, -0.5f,  0.5f), vec3(1.0f),
    vec3( 0.5f,  0.5f,  0.5f), vec3(1.0f),
    vec3( 0.5f,  0.5f,  0.5f), vec3(1.0f),
    vec3(-0.5f,  0.5f,  0.5f), vec3(1.0f),
    vec3(-0.5f, -0.5f,  0.5f), vec3(1.0f),
    
    vec3(-0.5f,  0.5f,  0.5f), vec3(1.0f),
    vec3(-0.5f,  0.5f, -0.5f), vec3(1.0f),
    vec3(-0.5f, -0.5f, -0.5f), vec3(1.0f),
    vec3(-0.5f, -0.5f, -0.5f), vec3(1.0f),
    vec3(-0.5f, -0.5f,  0.5f), vec3(1.0f),
    vec3(-0.5f,  0.5f,  0.5f), vec3(1.0f),
    
    vec3(0.5f,  0.5f,  0.5f), vec3(1.0f),
    vec3(0.5f,  0.5f, -0.5f), vec3(1.0f),
    vec3(0.5f, -0.5f, -0.5f), vec3(1.0f),
    vec3(0.5f, -0.5f, -0.5f), vec3(1.0f),
    vec3(0.5f, -0.5f,  0.5f), vec3(1.0f),
    vec3(0.5f,  0.5f,  0.5f), vec3(1.0f),
    
    vec3(-0.5f, -0.5f, -0.5f), vec3(1.0f),
    vec3( 0.5f, -0.5f, -0.5f), vec3(1.0f),
    vec3( 0.5f, -0.5f,  0.5f), vec3(1.0f),
    vec3( 0.5f, -0.5f,  0.5f), vec3(1.0f),
    vec3(-0.5f, -0.5f,  0.5f), vec3(1.0f),
    vec3(-0.5f, -0.5f, -0.5f), vec3(1.0f),
    
    vec3(-0.5f,  0.5f, -0.5f), vec3(1.0f),
    vec3( 0.5f,  0.5f, -0.5f), vec3(1.0f),
    vec3( 0.5f,  0.5f,  0.5f), vec3(1.0f),
    vec3( 0.5f,  0.5f,  0.5f), vec3(1.0f),
    vec3(-0.5f,  0.5f,  0.5f), vec3(1.0f),
    vec3(-0.5f,  0.5f, -0.5f), vec3(1.0f)
};

const int Light::verticesSize = sizeof(Light::vertices);
const int Light::numVertices = Light::verticesSize / sizeof(Light::Vertex);


Light::Light() :
    shader(ShaderLoader(vertexFilePath, fragmentFilePath))
{
    /* --- generate buffers ---*/
    glGenVertexArrays(1, &lightVAO);
    glGenBuffers(1, &lightVBO);
    
    /* --- bind buffers ---*/
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
    
    /* --- bind data --- */
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_DYNAMIC_DRAW);
    
    /* --- setGeometry --- */
    GLint stride = sizeof(Vertex);
    GLint positionAttrib = glGetAttribLocation(shader.getProgram(), "position"); // 0
    glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)0);
    glEnableVertexAttribArray(positionAttrib);
    
    GLint colorAttrib = glGetAttribLocation(shader.getProgram(), "lightObjectColor"); // 1
    glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(sizeof(vec3)));
    glEnableVertexAttribArray(colorAttrib);
    
    /* --- free recources --- */
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
};

void Light::render() {
    shader.use();
    
    glm::mat4 fullMatrix, model, view, projection;
    
    /* --- model to view --- */
    model = glm::scale(model, glm::vec3(0.2f));
    model = glm::translate(model, vec3(1.2f, 1.0f, 3.0f));
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

void Light::clear() {
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &lightVBO);
}
