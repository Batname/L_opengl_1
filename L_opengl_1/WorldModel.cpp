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

GLuint WorldModel::loadTextures(char* texturePath)
{
    GLuint textureID;
    glGenTextures(1, &textureID);
    int width, height;
    unsigned char* image;
    // Diffuse map
    image = SOIL_load_image(texturePath, &width, &height, 0, SOIL_LOAD_RGB);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    return textureID;
}

void WorldModel::clear()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
