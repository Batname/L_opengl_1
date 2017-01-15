#include "WorldModel.hpp"
#include "Game.hpp"

extern Game *game;

using namespace std;
using namespace glm;

WorldModel::WorldModel(const char* vertexFilePath, const char* fragmentFilePath) :
    Model(vertexFilePath, fragmentFilePath)
{
}

void WorldModel::renderLight() const
{
    /* --- bind ligth --- */
    GLint lightColorLoc  = glGetUniformLocation(shader.getProgram(), "lightColor");
    GLint ambientStrengthLoc = glGetUniformLocation(shader.getProgram(), "ambientStrength");
    glUniform3f(lightColorLoc,  1.0f, 1.0f, 1.0f);
    glUniform1f(ambientStrengthLoc, 0.1f);
    
    /* --- bind light position --- */
    GLint lightPositionLoc = glGetUniformLocation(shader.getProgram(), "lightPos");
    glUniform3f(lightPositionLoc, game->lightPosition.x, game->lightPosition.y, game->lightPosition.z);
}

void WorldModel::preRender() const
{
    shader.use();
}

void WorldModel::draw() const
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, numVertices);
    glBindVertexArray(0);
}

void WorldModel::renderTextures() const
{
}

void WorldModel::loadTextures(char* texturePath, GLuint* texture) const
{
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);
    
    // texture filters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    // texture mipmaps
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // loan and generate mipmaps
    int width, height;
    unsigned char *image = SOIL_load_image(texturePath, &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    
    // clear
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void WorldModel::clear() const
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
