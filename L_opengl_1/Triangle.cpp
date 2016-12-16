#include "Triangle.hpp"

Triangle::Triangle(GLint verticesSize, GLfloat * vertices, GLsizei verticesQty, GLchar * vertexPath, GLchar * fragmentPath) :
    verticesSize(verticesSize),
    vertices(vertices),
    verticesQty(verticesQty),
    shader(ShaderLoader(vertexPath, fragmentPath))
{
    bindVBO();
    bindVAO();
    bindTexture();
    setAttributesPointers();
    loadTexture("resources/textures/container.jpg");
    unbind();
}

Triangle::Triangle(GLint verticesSize, GLfloat * vertices, GLint indicesSize, GLuint * indices, GLchar * vertexPath, GLchar * fragmentPath) :
    verticesSize(verticesSize),
    vertices(vertices),
    indicesSize(indicesSize),
    indices(indices),
    verticesQty(indicesSize / sizeof(GLuint)),
    shader(ShaderLoader(vertexPath, fragmentPath))
{
    bindVBO();
    bindVAO();
    bindEBO();
    bindTexture();
    setAttributesPointers();
    loadTexture("resources/textures/container.jpg");
    unbind();
}

void Triangle::bindVBO()
{
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

void Triangle::bindVAO()
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
}

void Triangle::bindEBO()
{
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);
}

void Triangle::bindTexture()
{
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Triangle::setAttributesPointers()
{
    GLint stride = 8 * sizeof(GLfloat);
    
    // position
    GLint positionAttrib = glGetAttribLocation(shader.getProgram(), "position"); // 0
    glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)0);
    glEnableVertexAttribArray(positionAttrib);
    
    // color
    GLint colorAttrib = glGetAttribLocation(shader.getProgram(), "color"); // 1
    glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(colorAttrib);
    
    // texture
    GLint textureAttrib = glGetAttribLocation(shader.getProgram(), "texture"); // 2
    glVertexAttribPointer(textureAttrib, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(textureAttrib);
    
}

void Triangle::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Triangle::loadTexture(char * texturePath)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // loan and generate mipmaps
    int width, height;
    unsigned char *image = SOIL_load_image(texturePath, &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    // clear
    SOIL_free_image_data(image);
}

void Triangle::render()
{
    // bind textures
    glBindTexture(GL_TEXTURE_2D, texture);
    
    shader.use();
    
    glBindVertexArray(VAO);
    if (indices != nullptr) {
        glDrawElements(GL_TRIANGLES, verticesQty, GL_UNSIGNED_INT, 0);
    } else {
        glDrawArrays(GL_TRIANGLES, 0, verticesQty);
    }
    glBindVertexArray(0);
}

void Triangle::clear()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
