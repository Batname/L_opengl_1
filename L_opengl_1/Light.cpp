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
    glEnableVertexAttribArray(positionAttrib);
    
    /* --- free recources --- */
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
};

void Light::render() {
    shader.use();
    
    glm::mat4 fullMatrix;
    // model to world
    glm::mat4 model(1.0f);
    // world to view
    glm::mat4 view = game->getCamera()->GetViewMatrix();
    // view to clip space
    glm::mat4 projection = glm::perspective(45.0f, (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);
    
    // model to view
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
    model = glm::translate(model, vec3(1.0f));
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    
    fullMatrix = projection * view * model;
    
    /* use uniform matrix transformation */
    glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "fullMatrix"), 1, GL_FALSE, glm::value_ptr(mat4(1.0f)));
    
    /* Draw light object */
    glBindVertexArray(lightVAO);
//    glDrawArrays(GL_TRIANGLES, 0, numVertices);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
    
}

void Light::clear() {
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &lightVBO);
}
