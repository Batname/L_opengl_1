#include "ModelLoader.hpp"

ModelLoader::ModelLoader(const GLchar* path)
{
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        cout << "ERROR::ASIMP::" << import.GetErrorString() << endl;
        exit(EXIT_FAILURE);
    }
    
    string stringPath(path);
    directory = stringPath.substr(0, stringPath.find_last_of('/'));
    processNode(scene->mRootNode, scene);
}

void ModelLoader::draw(class ShaderLoader shader) const
{

}

void ModelLoader::processNode(struct aiNode* node, const aiScene* scene)
{
    for (GLuint i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    
    for(GLuint i = 0; i < node->mNumMeshes; i++) {
        processNode(node->mChildren[i], scene);
    }
}

ModelMesh ModelLoader::processMesh(struct aiMesh* mesh, const aiScene* scene)
{
    vector<OriginVertex> vertices;
    vector<GLuint> indices;
    vector<OriginTexture> textures;
    
    /* --- vertices --- */
    for(GLuint i = 0; i < mesh->mNumVertices; i++) {
        OriginVertex vertex;
        vec3 vector;
        
        /* --- positions --- */
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;
        
        /* --- normals --- */
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.normal = vector;
        
        /* --- texture coordinates --- */
        if (mesh->mTextureCoords[0]) {
            vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.texCoords = vec;
        } else {
            vertex.texCoords = vec2(0.0f, 0.0f);
        }
        
        vertices.push_back(vertex);
    }
    
    /* --- indices --- */
    for(GLuint i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for(GLuint j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }
    
    /* --- materials --- */
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        vector<OriginTexture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    
        vector<OriginTexture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }
    
    return ModelMesh(vertices, indices, textures);
}

vector<OriginTexture> ModelLoader::loadMaterialTextures(aiMaterial* mat, enum aiTextureType type, string typeName)
{
    vector<OriginTexture> textures;
    
    for (GLuint i = 0; i < mat->GetTextureCount(type); i++ ) {
        aiString str;
        mat->GetTexture(type, i, &str);
        
        /* --- Check if texture was loaded before and if so, continue to next iteration: skip loading a new texture --- */
        GLboolean skip = false;
        
        for (GLuint j = 0; j < textures_loaded.size(); j++) {
            if( textures_loaded[j].path == str ) {
                textures.push_back(textures_loaded[j]);
                skip = true;
                
                break;
            }
        }
        
        /* --- If texture hasn't been loaded already, load it --- */
        if( !skip ) {
            OriginTexture texture;
            texture.id = TextureFromFile(str.C_Str(), directory);
            texture.type = typeName;
            texture.path = str;
            textures.push_back( texture );
            
            textures_loaded.push_back( texture );
        }
    }
    
    return textures;
}

GLint ModelLoader::TextureFromFile(const char *path, string directory) const
{
    /* --- Generate texture ID and load texture data --- */
    string filename = string( path );
    filename = directory + '/' + filename;
    GLuint textureID;
    glGenTextures(1, &textureID);
    
    int width, height;
    
    unsigned char *image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
    
    // Assign texture to ID
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D );
    
    // Parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0 );
    SOIL_free_image_data(image);
    
    return textureID;
}
