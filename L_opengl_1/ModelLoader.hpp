#ifndef ModelLoader_hpp
#define ModelLoader_hpp

#include "includes.h"
#include "ShaderLoader.hpp"
#include "ModelMesh.hpp"
#include "VertexTypes.h"
#include "Model.hpp"

using namespace std;
using namespace glm;

class ModelLoader : public Model
{
public:
    ModelLoader(const GLchar* path, const char* vertexFilePath, const char* fragmentFilePath);
    virtual void render();
private:    
    vector<ModelMesh> meshes;
    string directory;
    vector<OriginTexture> textures_loaded;
    
    virtual void processNode(const aiNode* node, const aiScene* scene);
    virtual ModelMesh processMesh(const aiMesh* mesh, const aiScene* scene);
    virtual vector<OriginTexture> loadMaterialTextures(const aiMaterial* mat, enum aiTextureType type, string typeName);
    virtual GLint TextureFromFile(const char *path, string directory) const;
    
    virtual void draw();
    virtual void rendelModel() const;

};

#endif /* ModelLoader_hpp */
