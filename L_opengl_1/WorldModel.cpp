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
    GLint matAmbientStrLoc = glGetUniformLocation(shader.getProgram(), "material.ambientStr");
    GLint matDiffuseStrLoc = glGetUniformLocation(shader.getProgram(), "material.diffuseStr");
    GLint matSpecularLoc = glGetUniformLocation(shader.getProgram(), "material.specular");
    GLint matShineLoc    = glGetUniformLocation(shader.getProgram(), "material.shininess");
    
    GLint lightAmbientLoc  = glGetUniformLocation(shader.getProgram(), "light.ambient");
    GLint lightDiffuseLoc  = glGetUniformLocation(shader.getProgram(), "light.diffuse");
    GLint lightSpecularLoc = glGetUniformLocation(shader.getProgram(), "light.specular");
    
    GLint lightPositionLoc = glGetUniformLocation(shader.getProgram(), "light.position");
    GLint viewPositionLoc = glGetUniformLocation(shader.getProgram(), "viewPos");
    
    /* --- set light material --- */
    vec3 ambientStrengh = glm::vec3(0.2f); // Low influence
    vec3 diffuseStrengh = glm::vec3(0.5f); // Decrease the influence
    glUniform3f(matAmbientStrLoc, ambientStrengh.x, ambientStrengh.y, ambientStrengh.x);
    glUniform3f(matDiffuseStrLoc,  diffuseStrengh.x, diffuseStrengh.y, diffuseStrengh.x);
    glUniform3f(matSpecularLoc, 0.5f, 0.5f, 0.5f);
    glUniform1f(matShineLoc,    32.0f);
    
    /* --- set light power --- */
    glUniform3f(lightAmbientLoc,  0.2f, 0.2f, 0.2f);
    glUniform3f(lightDiffuseLoc,  0.5f, 0.5f, 0.5f); // Let's darken the light a bit to fit the scene
    glUniform3f(lightSpecularLoc, 1.0f, 1.0f, 1.0f);
    
    /* --- bind light position --- */
    glUniform3f(lightPositionLoc, game->lightPosition.x, game->lightPosition.y, game->lightPosition.z);
    
    /* --- bind camera position --- */
    glUniform3f(viewPositionLoc, game->getCamera()->GetPosition()->x, game->getCamera()->GetPosition()->y, game->getCamera()->GetPosition()->z);
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
