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
    
    /* --- load objects --- */
    lightObjects = ShapeGenerator::getLights();
    
    /* --- clean --- */
    plane.clean();
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Plane::renderLight() const
{
    /* --- set constants --- */
    vec3 ambientStrengh = glm::vec3(0.2f); // Low influence
    vec3 diffuseStrengh = glm::vec3(0.5f); // Decrease the influence
    
    /* --- camera position --- */
    glUniform3f(glGetUniformLocation(shader.getProgram(), "viewPos"), game->getCamera()->GetPosition()->x, game->getCamera()->GetPosition()->y, game->getCamera()->GetPosition()->z);
    
    /* --- matherials --- */
    glUniform3f(glGetUniformLocation(shader.getProgram(), "material.ambientStr"), ambientStrengh.x, ambientStrengh.y, ambientStrengh.x);
    glUniform3f(glGetUniformLocation(shader.getProgram(), "material.diffuseStr"),  diffuseStrengh.x, diffuseStrengh.y, diffuseStrengh.x);
    glUniform3f(glGetUniformLocation(shader.getProgram(), "material.specular"), 0.5f, 0.5f, 0.5f);
    glUniform1f(glGetUniformLocation(shader.getProgram(), "material.shininess"),    32.0f);
    
    /* --- direction light --- */
    glUniform3f(glGetUniformLocation(shader.getProgram(), "dirLight.direction"), 0.0f, 0.0f, 0.0f); // does not calculate it now
    glUniform3f(glGetUniformLocation(shader.getProgram(), "dirLight.ambient"), 0.05f, 0.05f, 0.05f);
    glUniform3f(glGetUniformLocation(shader.getProgram(), "dirLight.diffuse"), 0.4f, 0.4f, 0.4f);
    glUniform3f(glGetUniformLocation(shader.getProgram(), "dirLight.specular"), 0.5f, 0.5f, 0.5f);

    /* --- point lights --- */
    for (unsigned int i = 0; i < lightObjects.size; i++) {
        std::string number = std::to_string(i);
        
        glUniform3f(glGetUniformLocation(shader.getProgram(), ("pointLights[" + number + "].position").c_str()), lightObjects.positions[i].x, lightObjects.positions[i].y, lightObjects.positions[i].z);
        glUniform3f(glGetUniformLocation(shader.getProgram(), ("pointLights[" + number + "].ambient").c_str()),  0.05f, 0.05f, 0.05f);
        glUniform3f(glGetUniformLocation(shader.getProgram(), ("pointLights[" + number + "].diffuse").c_str()),  0.8, 0.8f, 0.8f);
        glUniform3f(glGetUniformLocation(shader.getProgram(), ("pointLights[" + number + "].specular").c_str()), 1.0f, 1.0f, 1.0f);
        glUniform1f(glGetUniformLocation(shader.getProgram(), ("pointLights[" + number + "].constant").c_str()), 1.0f);
        glUniform1f(glGetUniformLocation(shader.getProgram(), ("lpointLights[" + number + "].linear").c_str()), 0.09f);
        glUniform1f(glGetUniformLocation(shader.getProgram(), ("pointLights[" + number + "].quadratic").c_str()), 0.032f);
    }
    
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
    lightObjects.clean();
}
