#include "Light.hpp"

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
    /* --- bindVBO ---*/
    glGenVertexArrays(1, &lightVBO);
    glBindVertexArray(lightVBO);
    
    /* --- bindVAO ---*/
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
    
    /* --- setGeometry ----*/
    GLint stride = sizeof(Vertex);
    GLint positionAttrib = glGetAttribLocation(shader.getProgram(), "position"); // 0
    glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)0);
    glEnableVertexAttribArray(positionAttrib);
    
    GLint colorAttrib = glGetAttribLocation(shader.getProgram(), "lightObjectColor"); // 1
    glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(sizeof(vec3)));
    glEnableVertexAttribArray(positionAttrib);
};

void Light::render() {
    shader.use();
    
    /* use uniform matrix transformation */
    glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "fullMatrix"), 1, GL_FALSE, glm::value_ptr(mat4(1.0f)));
    
    /* Draw light object */
    glBindVertexArray(lightVAO);
    glDrawArrays(GL_TRIANGLES, 0, numVertices);
    glBindVertexArray(0);
    
}
