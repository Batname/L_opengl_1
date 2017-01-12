#ifndef Light_hpp
#define Light_hpp

#include "ShaderLoader.hpp"
#include "includes.h"

using namespace glm;

class Light
{
public:
    struct Vertex {
        vec3 position;
        vec3 color;
    };
    
    const static Vertex vertices[];
    const static int verticesSize;
    const static int numVertices;

    
    constexpr static char* vertexFilePath   = "resources/shaders/light.vs";
    constexpr static char* fragmentFilePath = "resources/shaders/light.frag";

    Light();

    void render();
    void clean();
private:
    GLuint lightVAO;
    GLuint lightVBO;
    ShaderLoader shader;

};

#endif /* Light_hpp */
