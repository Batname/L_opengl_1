#include "ModelMesh.hpp"

using namespace std;

ModelMesh::ModelMesh(vector<OriginVertex> vertices, vector<GLuint> indices, vector<OriginTexture> textures) :
    vertices(vertices), indices(indices), textures(textures)
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(OriginVertex), &vertices[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
    
    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(OriginVertex), (GLvoid *)0);
    
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(OriginVertex), (GLvoid *)offsetof(OriginVertex, normal));
    
    // vertex texture coordinates
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(OriginVertex), (GLvoid *)offsetof(OriginVertex, texCoords));
    
    glBindVertexArray(0);
}

void ModelMesh::draw(const class ShaderLoader* shader) const
{
    GLuint diffuseNr = 1;
    GLuint specularNr = 1;
    
    for (GLuint i = 0; i < textures.size(); i++) {
        
        glActiveTexture(GL_TEXTURE0 + i);
        stringstream ss;
        string number;
        string name = textures[i].type;
        
        if ("texture_diffuse" == name) {
            ss << diffuseNr++;
        } else if ("texture_specular" == name) {
            ss << specularNr++;
        }
        
        number = ss.str();
        
        glUniform1i(glGetUniformLocation(shader->getProgram(), (name + number).c_str()), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    
    glUniform1f(glGetUniformLocation(shader->getProgram(), "material.shinines"), 16.0f);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    
    for (GLuint i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void ModelMesh::clear() const
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

ModelMesh::~ModelMesh()
{

}
