#ifndef VertexTypes_h
#define VertexTypes_h

using namespace glm;
using namespace std;

struct RegularVertex
{
    vec3 position;
    vec3 color;
    vec3 normal;
};

struct SimpleVertex
{
    vec3 position;
    vec3 color;
};

struct VertexPosTexNorm
{
    vec3 position;
    vec2 texture;
    vec3 normal;
};

struct OriginVertex
{
    vec3 position;
    vec3 normal;
    vec2 texCoords;
};

typedef struct {
    GLuint id;
    string type;
    aiString path;
} OriginTexture;


#endif /* VertexTypes_h */
