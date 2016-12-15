#ifndef ShaderLoader_hpp
#define ShaderLoader_hpp

#include "includes.h"

class ShaderLoader
{
public:
    ShaderLoader(const GLchar * vertexPath, const GLchar * fragmentPath);
    void use();
    
    // getters
    GLuint getProgram();
    GLuint getVertexShader();
    GLuint getFragmentShader();

private:
    GLuint program;
    
    const GLchar *_vertexPath;
    const GLchar *_fragmentPath;
    
    void compile();
};

#endif /* ShaderLoader_hpp */
