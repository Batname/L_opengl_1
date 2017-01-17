#include "Plane.hpp"
#include "Game.hpp"

extern Game *game;

using namespace std;
using namespace glm;

Plane::Plane(const char* vertexFilePath, const char* fragmentFilePath) :
    WorldModel(vertexFilePath, fragmentFilePath)
{
    /* --- generate buffers --- */
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    /* --- bind buffers --- */
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    /* --- make object --- */
    ShapeData<RegularVertex> plane = ShapeGenerator::makePlane();
    numVertices = WorldModel::numVertices = plane.numVertices;
    
    /* --- buffer data --- */
    glBufferData(GL_ARRAY_BUFFER, plane.vertexBufferSize(), plane.vertices, GL_DYNAMIC_DRAW);
    
    /* --- setGeometry --- */
    GLint positionAttrib = glGetAttribLocation(shader.getProgram(), "position"); // 0
    glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE, plane.getStride(), (GLvoid*)0);
    glEnableVertexAttribArray(positionAttrib);
    
    GLint colorAttrib = glGetAttribLocation(shader.getProgram(), "color"); // 1
    glVertexAttribPointer(colorAttrib, 3, GL_FLOAT, GL_FALSE, plane.getStride(), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(colorAttrib);
    
    GLint normalAttrib = glGetAttribLocation(shader.getProgram(), "normal"); // 2
    glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, GL_FALSE, plane.getStride(), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(normalAttrib);
    
    /* --- clean --- */
    plane.clean();
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Plane::renderLight() const
{
    GLint matAmbientStrLoc = glGetUniformLocation(shader.getProgram(), "material.ambientStr");
    GLint matDiffuseStrLoc = glGetUniformLocation(shader.getProgram(), "material.diffuseStr");
    GLint matSpecularLoc = glGetUniformLocation(shader.getProgram(), "material.specular");
    GLint matShineLoc    = glGetUniformLocation(shader.getProgram(), "material.shininess");
    
    GLint lightAmbientLoc  = glGetUniformLocation(shader.getProgram(), "light.ambient");
    GLint lightDiffuseLoc  = glGetUniformLocation(shader.getProgram(), "light.diffuse");
    GLint lightSpecularLoc = glGetUniformLocation(shader.getProgram(), "light.specular");
    
    GLint lightConstantLoc = glGetUniformLocation(shader.getProgram(), "light.constant");
    GLint lightLinearLoc = glGetUniformLocation(shader.getProgram(), "light.linear");
    GLint lightQuadraticLoc = glGetUniformLocation(shader.getProgram(), "light.quadratic");
    
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
    
    glUniform1f(lightConstantLoc, 1.0f);
    glUniform1f(lightLinearLoc, 0.09f);
    glUniform1f(lightQuadraticLoc, 0.032f);
    
    /* --- bind light position --- */
    glUniform3f(lightPositionLoc, game->lightPosition.x, game->lightPosition.y, game->lightPosition.z);
    
    /* --- bind camera position --- */
    glUniform3f(viewPositionLoc, game->getCamera()->GetPosition()->x, game->getCamera()->GetPosition()->y, game->getCamera()->GetPosition()->z);
}

void Plane::renderModel() const
{
    /* --- define transformation matrix --- */
    glm::mat4 fullMatrix, model, view, projection;
    
    /* --- model to view, send it to shader --- */
    model = glm::translate(model, vec3(0.0f));
    model = glm::scale(model, glm::vec3(15.0f, 1.0f, 15.0f));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "model"), 1, GL_FALSE, &model[0][0]);
    
    /* --- world to view --- */
    view = game->getCamera()->GetViewMatrix();
    
    /* --- view to clip space --- */
    projection = game->getCamera()->GetProjection();
    
    /* use uniform matrix transformation */
    fullMatrix = projection * view * model;
    glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "fullMatrix"), 1, GL_FALSE, &fullMatrix[0][0]);
}

void Plane::render() const
{
    this->preRender();
    renderModel();
    this->renderLight();
    this->draw();
}

void Plane::clear()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
