#include "ShapeGenerator.hpp"

ShapeData<RegularVertex> ShapeGenerator::makePlane()
{
    ShapeData<RegularVertex> ret;
    
    RegularVertex verts[] = {
        glm::vec3(+0.0f, +1.0f, +0.5),  // position
        glm::vec3(+0.5f, +0.5f, +0.5),  // color
        glm::vec3(+1.0f, +0.0f, +0.0f), // normal
        
        glm::vec3(+1.0f, -1.0f, +0.5),
        glm::vec3(+0.5f, +0.5f, +0.5),
        glm::vec3(+0.0f, +1.0f, +0.0f),
        
        glm::vec3(-1.0f, -1.0f, +0.5),
        glm::vec3(+0.5f, +0.5f, +0.5),
        glm::vec3(+0.0f, +0.0f, +1.0f)
    };
    
    ret.numVertices = NUM_ARRAY_ELEMENTS(verts);
    ret.vertices = (RegularVertex*)malloc(sizeof(verts));
    memcpy(ret.vertices, verts, sizeof(verts));
    
    return ret;
}
