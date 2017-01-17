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
    
    /* --- load objects --- */
    objectsData = ShapeGenerator::getCubes();
    lightObjects = ShapeGenerator::getLights();
        
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
    glUniform3f(glGetUniformLocation(shader.getProgram(), "viewPos"), game->getCamera()->GetPosition()->x, game->getCamera()->GetPosition()->y, game->getCamera()->GetPosition()->z);
    
    glUniform1f(glGetUniformLocation(shader.getProgram(), "material.shininess"), 32.0f);
    
    /* --- direction light --- */
    glUniform3f(glGetUniformLocation(shader.getProgram(), "dirLight.direction"), -0.2f, -1.0f, -0.3f);
    glUniform3f(glGetUniformLocation(shader.getProgram(), "dirLight.ambient"), 0.05f, 0.05f, 0.05f);
    glUniform3f(glGetUniformLocation(shader.getProgram(), "dirLight.diffuse"), 0.4f, 0.4f, 0.4f);
    glUniform3f(glGetUniformLocation(shader.getProgram(), "dirLight.specular"), 0.5f, 0.5f, 0.5f);

    /* --- point lights --- */
    // Point light 1
    glUniform3f(glGetUniformLocation(shader.getProgram(), "pointLights[0].position"), lightObjects.positions[0].x, lightObjects.positions[0].y, lightObjects.positions[0].z);
    glUniform3f(glGetUniformLocation(shader.getProgram(), "pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);
    glUniform3f(glGetUniformLocation(shader.getProgram(), "pointLights[0].diffuse"), 0.8f, 0.8f, 0.8f);
    glUniform3f(glGetUniformLocation(shader.getProgram(), "pointLights[0].specular"), 1.0f, 1.0f, 1.0f);
    glUniform1f(glGetUniformLocation(shader.getProgram(), "pointLights[0].constant"), 1.0f);
    glUniform1f(glGetUniformLocation(shader.getProgram(), "pointLights[0].linear"), 0.09);
    glUniform1f(glGetUniformLocation(shader.getProgram(), "pointLights[0].quadratic"), 0.032);
    // Point light 2
    glUniform3f(glGetUniformLocation(shader.getProgram(), "pointLights[1].position"), lightObjects.positions[1].x, lightObjects.positions[1].y, lightObjects.positions[1].z);
    glUniform3f(glGetUniformLocation(shader.getProgram(), "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
    glUniform3f(glGetUniformLocation(shader.getProgram(), "pointLights[1].diffuse"), 0.8f, 0.8f, 0.8f);
    glUniform3f(glGetUniformLocation(shader.getProgram(), "pointLights[1].specular"), 1.0f, 1.0f, 1.0f);
    glUniform1f(glGetUniformLocation(shader.getProgram(), "pointLights[1].constant"), 1.0f);
    glUniform1f(glGetUniformLocation(shader.getProgram(), "pointLights[1].linear"), 0.09);
    glUniform1f(glGetUniformLocation(shader.getProgram(), "pointLights[1].quadratic"), 0.032);
    // Point light 3
    glUniform3f(glGetUniformLocation(shader.getProgram(), "pointLights[2].position"), lightObjects.positions[2].x, lightObjects.positions[2].y, lightObjects.positions[2].z);
    glUniform3f(glGetUniformLocation(shader.getProgram(), "pointLights[2].ambient"), 0.05f, 0.05f, 0.05f);
    glUniform3f(glGetUniformLocation(shader.getProgram(), "pointLights[2].diffuse"), 0.8f, 0.8f, 0.8f);
    glUniform3f(glGetUniformLocation(shader.getProgram(), "pointLights[2].specular"), 1.0f, 1.0f, 1.0f);
    glUniform1f(glGetUniformLocation(shader.getProgram(), "pointLights[2].constant"), 1.0f);
    glUniform1f(glGetUniformLocation(shader.getProgram(), "pointLights[2].linear"), 0.09);
    glUniform1f(glGetUniformLocation(shader.getProgram(), "pointLights[2].quadratic"), 0.032);
    // Point light 4
    glUniform3f(glGetUniformLocation(shader.getProgram(), "pointLights[3].position"), lightObjects.positions[3].x, lightObjects.positions[3].y, lightObjects.positions[3].z);
    glUniform3f(glGetUniformLocation(shader.getProgram(), "pointLights[3].ambient"), 0.05f, 0.05f, 0.05f);
    glUniform3f(glGetUniformLocation(shader.getProgram(), "pointLights[3].diffuse"), 0.8f, 0.8f, 0.8f);
    glUniform3f(glGetUniformLocation(shader.getProgram(), "pointLights[3].specular"), 1.0f, 1.0f, 1.0f);
    glUniform1f(glGetUniformLocation(shader.getProgram(), "pointLights[3].constant"), 1.0f);
    glUniform1f(glGetUniformLocation(shader.getProgram(), "pointLights[3].linear"), 0.09);
    glUniform1f(glGetUniformLocation(shader.getProgram(), "pointLights[3].quadratic"), 0.032);
    
    /* --- SpotLight --- */
    glUniform3f(glGetUniformLocation(shader.getProgram(), "spotLight.position"), game->getCamera()->GetPosition()->x, game->getCamera()->GetPosition()->y, game->getCamera()->GetPosition()->z);
    glUniform3f(glGetUniformLocation(shader.getProgram(), "spotLight.direction"), game->getCamera()->GetFront().x, game->getCamera()->GetFront().y, game->getCamera()->GetFront().z);
    glUniform3f(glGetUniformLocation(shader.getProgram(), "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
    glUniform3f(glGetUniformLocation(shader.getProgram(), "spotLight.diffuse"), 1.0f, 1.0f, 1.0f);
    glUniform3f(glGetUniformLocation(shader.getProgram(), "spotLight.specular"), 1.0f, 1.0f, 1.0f);
    glUniform1f(glGetUniformLocation(shader.getProgram(), "spotLight.constant"), 1.0f);
    glUniform1f(glGetUniformLocation(shader.getProgram(), "spotLight.linear"), 0.09f);
    glUniform1f(glGetUniformLocation(shader.getProgram(), "spotLight.quadratic"), 0.032f);
    glUniform1f(glGetUniformLocation(shader.getProgram(), "spotLight.cutOff"), glm::cos(glm::radians(12.5f)));
    glUniform1f(glGetUniformLocation(shader.getProgram(), "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f)));
}

void Cube::renderModel() const
{
    mat4 view, projection;
    
    /* --- world to view --- */
    view = game->getCamera()->GetViewMatrix();
    
    /* --- view to clip space --- */
    projection = game->getCamera()->GetProjection();
    
    /* --- draw cubes --- */
    for(unsigned int i = 0; i < objectsData.size; i++) {
        mat4 model, fullMatrix;
        
        /* --- model to view, send it to shader --- */
        model = glm::translate(model, objectsData.positions[i]);
        model = glm::scale(model, glm::vec3(1.0f));
        model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "model"), 1, GL_FALSE, &model[0][0]);
        
        /* use uniform matrix transformation */
        fullMatrix = projection * view * model;
        glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "fullMatrix"), 1, GL_FALSE, &fullMatrix[0][0]);
        
        this->draw();
    }
    
}

void Cube::render() const
{
    this->preRender();
    renderLight();
    renderTextures();
    renderModel();
}

void Cube::clear()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    objectsData.clean();
    lightObjects.clean();
}
