#include "Cube.hpp"
#include "Game.hpp"

extern Game *game;

Cube::Cube(const char* vertexFilePath, const char* fragmentFilePath) :
    WorldModel(vertexFilePath, fragmentFilePath)
{
    /* --- generate buffers --- */
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    /* --- bind buffers --- */
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
    /* --- make object --- */
    ShapeData<VertexPosTexNorm> cube = ShapeGenerator::makeCube();
    numVertices = WorldModel::numVertices = cube.numVertices;
    
    /* --- buffer data --- */
    glBufferData(GL_ARRAY_BUFFER, cube.vertexBufferSize(), cube.vertices, GL_DYNAMIC_DRAW);
    
    /* --- setGeometry --- */
    GLint positionAttrib = glGetAttribLocation(shader.getProgram(), "position"); // 0
    glVertexAttribPointer(positionAttrib, 3, GL_FLOAT, GL_FALSE, cube.getStride(), (GLvoid*)0);
    glEnableVertexAttribArray(positionAttrib);
    
    GLint textureAttrib = glGetAttribLocation(shader.getProgram(), "texCoord"); // 1
    glVertexAttribPointer(textureAttrib, 2, GL_FLOAT, GL_FALSE, cube.getStride(), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(textureAttrib);
    
    GLint normalAttrib = glGetAttribLocation(shader.getProgram(), "normal"); // 2
    glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, GL_FALSE, cube.getStride(), (GLvoid*)(5 * sizeof(GLfloat)));
    glEnableVertexAttribArray(normalAttrib);
    
    /* --- load textures --- */
    diffuseMap = loadTextures("resources/textures/container2.png");
    specularMap = loadTextures("resources/textures/container2_specular.png");
    
    /* --- clean ---*/
    cube.clean();
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Cube::renderTextures() const
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuseMap);
    
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, specularMap);
}

void Cube::renderLight() const
{
    GLint matDiffuseLoc = glGetUniformLocation(shader.getProgram(), "material.diffuse");
    GLint matSpecularLoc = glGetUniformLocation(shader.getProgram(), "material.specular");
    GLint matShineLoc    = glGetUniformLocation(shader.getProgram(), "material.shininess");
    
    GLint lightAmbientLoc  = glGetUniformLocation(shader.getProgram(), "light.ambient");
    GLint lightDiffuseLoc  = glGetUniformLocation(shader.getProgram(), "light.diffuse");
    GLint lightSpecularLoc = glGetUniformLocation(shader.getProgram(), "light.specular");

    GLint lightPositionLoc = glGetUniformLocation(shader.getProgram(), "light.position");
    GLint viewPositionLoc = glGetUniformLocation(shader.getProgram(), "viewPos");
    
    /* --- set light material --- */
    glUniform1i(matDiffuseLoc,  0);
    glUniform1i(matSpecularLoc, 1);
    glUniform1f(matShineLoc,    32.0f);
    
    /* --- set light power --- */
    glUniform3f(lightAmbientLoc,  0.2f, 0.2f, 0.2f);
    glUniform3f(lightDiffuseLoc,  0.5f, 0.5f, 0.5f);
    glUniform3f(lightSpecularLoc, 1.0f, 1.0f, 1.0f);
    
    /* --- bind light position --- */
    glUniform3f(lightPositionLoc, game->lightPosition.x, game->lightPosition.y, game->lightPosition.z);
    
    /* --- bind camera position --- */
    glUniform3f(viewPositionLoc, game->getCamera()->GetPosition()->x, game->getCamera()->GetPosition()->y, game->getCamera()->GetPosition()->z);
}

void Cube::renderModel() const
{
    glm::mat4 fullMatrix, model, view, projection;
    
    /* --- model to view, send it to shader --- */
    model = glm::translate(model, vec3(0.0f));
    model = glm::scale(model, glm::vec3(1.0f));
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f));
    glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "model"), 1, GL_FALSE, &model[0][0]);
    
    /* --- world to view --- */
    view = game->getCamera()->GetViewMatrix();
    
    /* --- view to clip space --- */
    projection = game->getCamera()->GetProjection();
    
    /* use uniform matrix transformation */
    fullMatrix = projection * view * model;
    glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "fullMatrix"), 1, GL_FALSE, &fullMatrix[0][0]);
}

void Cube::render() const
{
    this->preRender();
    renderModel();
    renderLight();
    renderTextures();
    this->draw();
}

void Cube::clear() const
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
