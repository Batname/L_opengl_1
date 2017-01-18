#include "ModelMesh.hpp"

using namespace std;

ModelMesh::ModelMesh(vector<OriginVertex> vertices, vector<GLuint> indices, vector<OriginTexture> textures) :
    vertices(vertices), indices(indices), textures(textures)
{

}

void ModelMesh::draw(class ShaderLoader shader) const
{

}

ModelMesh::~ModelMesh()
{

}
