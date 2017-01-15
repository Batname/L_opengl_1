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
    loadTextures("resources/textures/container.jpg", &texture1);
    loadTextures("resources/textures/awesomeface.png", &texture2);
    
    /* --- clean ---*/
    cube.clean();
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Cube::renderTextures() const
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glUniform1i(glGetUniformLocation(shader.getProgram(), "ourTexture1"), 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glUniform1i(glGetUniformLocation(shader.getProgram(), "ourTexture2"), 1);
}

void Cube::renderLight() const
{
    GLint objectColorLoc = glGetUniformLocation(shader.getProgram(), "objectColor");
    GLint lightColorLoc  = glGetUniformLocation(shader.getProgram(), "lightColor");
    GLint ambientStrengthLoc = glGetUniformLocation(shader.getProgram(), "ambientStrength");
    glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.31f);
    glUniform3f(lightColorLoc,  1.0f, 1.0f, 1.0f);
    glUniform1f(ambientStrengthLoc, 0.1f);
    
    /* --- bind light position --- */
    GLint lightPositionLoc = glGetUniformLocation(shader.getProgram(), "lightPos");
    glUniform3f(lightPositionLoc, game->lightPosition.x, game->lightPosition.y, game->lightPosition.z);
    
    /* --- bind camera position --- */
    GLint viewPositionLoc = glGetUniformLocation(shader.getProgram(), "viewPos");
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
    this->draw();
}

void Cube::clear() const
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
