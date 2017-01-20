#ifndef ModelMesh_hpp
#define ModelMesh_hpp

#include "includes.h"

#include "ShaderLoader.hpp"
#include "VertexTypes.h"

using namespace std;

class ModelMesh
{
public:
    const vector<OriginVertex> vertices;
    const vector<GLuint> indices;
    const vector<OriginTexture> textures;
    
    ModelMesh(vector<OriginVertex> vertices, vector<GLuint> indices, vector<OriginTexture> textures);
    ~ModelMesh();

    virtual void draw(class ShaderLoader* shader) const;
    virtual void clear() const;
private:
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
};

#endif /* ModelMesh_hpp */
