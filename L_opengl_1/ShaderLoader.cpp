#include "ShaderLoader.hpp"

using namespace std;

ShaderLoader::ShaderLoader(const GLchar * vertexPath, const GLchar * fragmentPath) :
    _vertexPath(vertexPath), _fragmentPath(fragmentPath)
{
    compile();
}

void ShaderLoader::compile()
{
    // load shader code files
    string vertexCode;
    string fragmentCode;
    ifstream vShaderFile;
    ifstream fShaderFile;
    
    vShaderFile.exceptions(ifstream::badbit);
    fShaderFile.exceptions(ifstream::badbit);
    
    try {
        // open files
        vShaderFile.open(_vertexPath);
        fShaderFile.open(_fragmentPath);
        
        stringstream vShaderStream, fShaderStream;
        
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        
        vShaderFile.close();
        fShaderFile.close();
        
        // Convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    } catch (ifstream::failure e) {
        cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << endl;
    }
    
    const GLchar * vShaderCode = vertexCode.c_str();
    const GLchar * fShaderCode = fragmentCode.c_str();

    GLuint vertex, fragment;
    GLint success;
    GLchar infoLog[521];
    
    // Vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
    }
    
    // Fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        cout << "ERROR::SHADER::FRAFMENT::COMPILATION_FAILED\n" << infoLog << endl;
    }
    
    // Shader program
    program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    
    // Linking
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
    }
    
    // Clear, delete shaders what was linked into program
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

GLuint ShaderLoader::getProgram()
{
    return program;
}

void ShaderLoader::use()
{
    glUseProgram(program);
}
