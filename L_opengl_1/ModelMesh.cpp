#include "ModelMesh.hpp"

using namespace std;

ModelMesh::ModelMesh(vector<OriginVertex> vertices, vector<GLuint> indices, vector<OriginTexture> textures) :
    vertices(vertices), indices(indices), textures(textures)
{
    /* --- gen buffers --- */
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    /* --- bind buffers --- */
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(OriginVertex), &vertices[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
    
    /* --- vertex positions --- */
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(OriginVertex), (GLvoid*)0);
    
    /* --- vertex normals --- */
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(OriginVertex), (GLvoid*)offsetof(OriginVertex, normal));
    
    
    /* --- texture normals --- */
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(OriginVertex), (GLvoid*)offsetof(OriginVertex, texCoords));
}

void ModelMesh::draw(class ShaderLoader shader) const
{
    GLuint diffuseNr = 1;
    GLuint specularNr = 1;
    
    for (GLuint i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + 1);
        
        stringstream ss;
        string number;
        string name = textures[i].type;
        if (name == "texture_diffuse")
            ss << diffuseNr++;
        else if (name == "texture_specular")
            ss << specularNr++;
        number = ss.str();
        
        glUniform1f(glGetUniformLocation(shader.getProgram(), ("material." + name + number).c_str()), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }
    glActiveTexture(GL_TEXTURE0);
    
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

ModelMesh::~ModelMesh()
{

}
