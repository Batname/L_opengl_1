#include "WorldModel.hpp"


#include "Plane.hpp"
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

void WorldModel::draw() const
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, numVertices);
    glBindVertexArray(0);
}

void WorldModel::clear() const
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
