#ifndef VertexTypes_h
#define VertexTypes_h

#include "includes.h"

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


#endif /* VertexTypes_h */
