#include "Model.hpp"

Model::Model(const char* vertexFilePath, const char* fragmentFilePath) :
    shader(ShaderLoader(vertexFilePath, fragmentFilePath))
{

}

void Model::preRender() const
{
    shader.use();
}
