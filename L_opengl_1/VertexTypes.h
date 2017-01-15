#ifndef VertexTypes_h
#define VertexTypes_h

using namespace glm;

struct RegularVertex {
    vec3 position;
    vec3 color;
    vec3 normal;
};

struct SimpleVertex {
    vec3 position;
    vec3 color;
};

struct VertexPosTexNorm {
    vec3 position;
    vec2 texture;
    vec3 normal;
};


#endif /* VertexTypes_h */
