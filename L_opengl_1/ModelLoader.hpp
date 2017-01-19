#ifndef ModelLoader_hpp
#define ModelLoader_hpp

#include "includes.h"
#include "ShaderLoader.hpp"
#include "ModelMesh.hpp"
#include "VertexTypes.h"

using namespace std;
using namespace glm;

class ModelLoader
{
public:
    explicit ModelLoader(const GLchar* path);
    virtual void draw(class ShaderLoader shader) const;
private:
    vector<ModelMesh> meshes;
    string directory;
    vector<OriginTexture> textures_loaded;
    
    virtual void processNode(struct aiNode* node, const aiScene* scene);
    virtual ModelMesh processMesh(struct aiMesh* mesh, const aiScene* scene);
    virtual vector<OriginTexture> loadMaterialTextures(aiMaterial* mat, enum aiTextureType type, string typeName);
    virtual GLint TextureFromFile(const char *path, string directory) const;
};

#endif /* ModelLoader_hpp */
