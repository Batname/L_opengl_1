#include "ShapeGenerator.hpp"

ShapeData<SimpleVertex> ShapeGenerator::makePlane()
{
    ShapeData<SimpleVertex> ret;
    
    SimpleVertex verts[] = {
        glm::vec3(+0.0f, +1.0f, +0.5),
        glm::vec3(+1.0f, +0.0f, +0.0f),
        
        glm::vec3(+1.0f, -1.0f, +0.5),
        glm::vec3(+0.0f, +1.0f, +0.0f),
        
        glm::vec3(-1.0f, -1.0f, +0.5),
        glm::vec3(+0.0f, +0.0f, +1.0f)
    };
    
    ret.numVertices = NUM_ARRAY_ELEMENTS(verts);
    ret.vertices = (SimpleVertex*)malloc(sizeof(verts));
    memcpy(ret.vertices, verts, sizeof(verts));
    
    return ret;
}
