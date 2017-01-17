#include "ShapeGenerator.hpp"

using namespace glm;

ShapeData<RegularVertex> ShapeGenerator::makePlane()
{
    ShapeData<RegularVertex> ret;
    
    RegularVertex verts[] = {
        vec3(+0.5f, +0.5f, +0.5),  // position
        vec3(+0.5f, +0.5f, +0.5),  // color
        vec3(+1.0f, +0.0f, +0.0f), // normal
        
        vec3(+0.5f, -0.5f, +0.5),
        vec3(+0.5f, +0.5f, +0.5),
        vec3(+1.0f, +0.0f, +0.0f),
        
        vec3(-0.5f, +0.5f, +0.5),
        vec3(+0.5f, +0.5f, +0.5),
        vec3(+1.0f, +0.0f, +0.0f),
        
        
        vec3(+0.5f, -0.5f, +0.5),  // position
        vec3(+0.5f, +0.5f, +0.5),  // color
        vec3(+1.0f, +0.0f, +0.0f), // normal
        
        vec3(-0.5f, -0.5f, +0.5),
        vec3(+0.5f, +0.5f, +0.5),
        vec3(+1.0f, +0.0f, +0.0f),
        
        vec3(-0.5f, +0.5f, +0.5),
        vec3(+0.5f, +0.5f, +0.5),
        vec3(+1.0f, +0.0f, +0.0f)
    };
    
    ret.numVertices = NUM_ARRAY_ELEMENTS(verts, RegularVertex);
    ret.vertices = (RegularVertex*)malloc(sizeof(verts));
    memcpy(ret.vertices, verts, sizeof(verts));
    
    return ret;
}

ShapeData<SimpleVertex> ShapeGenerator::makeLight()
{
    ShapeData<SimpleVertex> ret;
    
    RegularVertex verts[] = {
        vec3(-0.5f, -0.5f, -0.5f), vec3(1.0f),
        vec3( 0.5f, -0.5f, -0.5f), vec3(1.0f),
        vec3( 0.5f,  0.5f, -0.5f), vec3(1.0f),
        vec3( 0.5f,  0.5f, -0.5f), vec3(1.0f),
        vec3(-0.5f,  0.5f, -0.5f), vec3(1.0f),
        vec3(-0.5f, -0.5f, -0.5f), vec3(1.0f),
        
        vec3(-0.5f, -0.5f,  0.5f), vec3(1.0f),
        vec3( 0.5f, -0.5f,  0.5f), vec3(1.0f),
        vec3( 0.5f,  0.5f,  0.5f), vec3(1.0f),
        vec3( 0.5f,  0.5f,  0.5f), vec3(1.0f),
        vec3(-0.5f,  0.5f,  0.5f), vec3(1.0f),
        vec3(-0.5f, -0.5f,  0.5f), vec3(1.0f),
        
        vec3(-0.5f,  0.5f,  0.5f), vec3(1.0f),
        vec3(-0.5f,  0.5f, -0.5f), vec3(1.0f),
        vec3(-0.5f, -0.5f, -0.5f), vec3(1.0f),
        vec3(-0.5f, -0.5f, -0.5f), vec3(1.0f),
        vec3(-0.5f, -0.5f,  0.5f), vec3(1.0f),
        vec3(-0.5f,  0.5f,  0.5f), vec3(1.0f),
        
        vec3(0.5f,  0.5f,  0.5f), vec3(1.0f),
        vec3(0.5f,  0.5f, -0.5f), vec3(1.0f),
        vec3(0.5f, -0.5f, -0.5f), vec3(1.0f),
        vec3(0.5f, -0.5f, -0.5f), vec3(1.0f),
        vec3(0.5f, -0.5f,  0.5f), vec3(1.0f),
        vec3(0.5f,  0.5f,  0.5f), vec3(1.0f),
        
        vec3(-0.5f, -0.5f, -0.5f), vec3(1.0f),
        vec3( 0.5f, -0.5f, -0.5f), vec3(1.0f),
        vec3( 0.5f, -0.5f,  0.5f), vec3(1.0f),
        vec3( 0.5f, -0.5f,  0.5f), vec3(1.0f),
        vec3(-0.5f, -0.5f,  0.5f), vec3(1.0f),
        vec3(-0.5f, -0.5f, -0.5f), vec3(1.0f),
        
        vec3(-0.5f,  0.5f, -0.5f), vec3(1.0f),
        vec3( 0.5f,  0.5f, -0.5f), vec3(1.0f),
        vec3( 0.5f,  0.5f,  0.5f), vec3(1.0f),
        vec3( 0.5f,  0.5f,  0.5f), vec3(1.0f),
        vec3(-0.5f,  0.5f,  0.5f), vec3(1.0f),
        vec3(-0.5f,  0.5f, -0.5f), vec3(1.0f)
    };
    
    ret.numVertices = NUM_ARRAY_ELEMENTS(verts, SimpleVertex);

    ret.vertices = (SimpleVertex*)malloc(sizeof(verts));
    memcpy(ret.vertices, verts, sizeof(verts));
    
    return ret;
}

ShapeData<VertexPosTexNorm> ShapeGenerator::makeCube()
{
    ShapeData<VertexPosTexNorm> ret;
    
    VertexPosTexNorm verts[] = {
        vec3(-0.5f, -0.5f, -0.5f),  vec2( 0.0f, 0.0),      vec3(0.0f,  0.0f, -1.0f),
        vec3(+0.5f, -0.5f, -0.5f),  vec2( 1.0f, 0.0),      vec3(0.0f,  0.0f, -1.0f),
        vec3(+0.5f,  0.5f, -0.5f),  vec2( 1.0f, 1.0),      vec3(0.0f,  0.0f, -1.0f),
        vec3(+0.5f,  0.5f, -0.5f),  vec2( 1.0f, 1.0),      vec3(0.0f,  0.0f, -1.0f),
        vec3(-0.5f,  0.5f, -0.5f),  vec2( 0.0f, 1.0),      vec3(0.0f,  0.0f, -1.0f),
        vec3(-0.5f, -0.5f, -0.5f),  vec2( 0.0f, 0.0),      vec3(0.0f,  0.0f, -1.0f),
        
        vec3(-0.5f, -0.5f,  0.5f),  vec2(0.0f, 0.0f),      vec3(0.0f,  0.0f, 1.0f),
        vec3(+0.5f, -0.5f,  0.5f),  vec2(1.0f, 0.0f),      vec3(0.0f,  0.0f, 1.0f),
        vec3(+0.5f,  0.5f,  0.5f),  vec2(1.0f, 1.0f),      vec3(0.0f,  0.0f, 1.0f),
        vec3(+0.5f,  0.5f,  0.5f),  vec2(1.0f, 1.0f),      vec3(0.0f,  0.0f, 1.0f),
        vec3(-0.5f,  0.5f,  0.5f),  vec2(0.0f, 1.0f),      vec3(0.0f,  0.0f, 1.0f),
        vec3(-0.5f, -0.5f,  0.5f),  vec2(0.0f, 0.0f),      vec3(0.0f,  0.0f, 1.0f),
        
        vec3(-0.5f,  0.5f,  0.5f),  vec2(1.0f, 0.0f),      vec3(-1.0f,  0.0f,  0.0f),
        vec3(-0.5f,  0.5f, -0.5f),  vec2(1.0f, 1.0f),      vec3(-1.0f,  0.0f,  0.0f),
        vec3(-0.5f, -0.5f, -0.5f),  vec2(0.0f, 1.0f),      vec3(-1.0f,  0.0f,  0.0f),
        vec3(-0.5f, -0.5f, -0.5f),  vec2(0.0f, 1.0f),      vec3(-1.0f,  0.0f,  0.0f),
        vec3(-0.5f, -0.5f,  0.5f),  vec2(0.0f, 0.0f),      vec3(-1.0f,  0.0f,  0.0f),
        vec3(-0.5f,  0.5f,  0.5f),  vec2(1.0f, 0.0f),      vec3(-1.0f,  0.0f,  0.0f),
        
        vec3(+0.5f,  0.5f,  0.5f),  vec2(1.0f, 0.0f),      vec3(1.0f,  0.0f,  0.0f),
        vec3(+0.5f,  0.5f, -0.5f),  vec2(1.0f, 1.0f),      vec3(1.0f,  0.0f,  0.0f),
        vec3(+0.5f, -0.5f, -0.5f),  vec2(0.0f, 1.0f),      vec3(1.0f,  0.0f,  0.0f),
        vec3(+0.5f, -0.5f, -0.5f),  vec2(0.0f, 1.0f),      vec3(1.0f,  0.0f,  0.0f),
        vec3(+0.5f, -0.5f,  0.5f),  vec2(0.0f, 0.0f),      vec3(1.0f,  0.0f,  0.0f),
        vec3(+0.5f,  0.5f,  0.5f),  vec2(1.0f, 0.0f),      vec3(1.0f,  0.0f,  0.0f),
        
        vec3(-0.5f, -0.5f, -0.5f),  vec2(0.0f, 1.0f),      vec3(0.0f, -1.0f,  0.0f),
        vec3(+0.5f, -0.5f, -0.5f),  vec2(1.0f, 1.0f),      vec3(0.0f, -1.0f,  0.0f),
        vec3(+0.5f, -0.5f,  0.5f),  vec2(1.0f, 0.0f),      vec3(0.0f, -1.0f,  0.0f),
        vec3(+0.5f, -0.5f,  0.5f),  vec2(1.0f, 0.0f),      vec3(0.0f, -1.0f,  0.0f),
        vec3(-0.5f, -0.5f,  0.5f),  vec2(0.0f, 0.0f),      vec3(0.0f, -1.0f,  0.0f),
        vec3(-0.5f, -0.5f, -0.5f),  vec2(0.0f, 1.0f),      vec3(0.0f, -1.0f,  0.0f),
        
        vec3(-0.5f,  0.5f, -0.5f),  vec2(0.0f, 1.0f),      vec3(0.0f,  1.0f,  0.0f),
        vec3(+0.5f,  0.5f, -0.5f),  vec2(1.0f, 1.0f),      vec3(0.0f,  1.0f,  0.0f),
        vec3(+0.5f,  0.5f,  0.5f),  vec2(1.0f, 0.0f),      vec3(0.0f,  1.0f,  0.0f),
        vec3(+0.5f,  0.5f,  0.5f),  vec2(1.0f, 0.0f),      vec3(0.0f,  1.0f,  0.0f),
        vec3(-0.5f,  0.5f,  0.5f),  vec2(0.0f, 0.0f),      vec3(0.0f,  1.0f,  0.0f),
        vec3(-0.5f,  0.5f, -0.5f),  vec2(0.0f, 1.0f),      vec3(0.0f,  1.0f,  0.0f)
    };
    
    ret.numVertices = NUM_ARRAY_ELEMENTS(verts, VertexPosTexNorm);
    
    ret.vertices = (VertexPosTexNorm*)malloc(sizeof(verts));
    memcpy(ret.vertices, verts, sizeof(verts));
    
    return ret;
}

ObjectsData ShapeGenerator::getCubes()
{
    ObjectsData ret;
    vec3 positions[] = {
        vec3(+1.0f, 0.0f, 1.0f),
        vec3(-1.0f, 0.0f, 1.0f),
        vec3(-3.0f, 0.0f, 1.0f),
        vec3(-5.0f, 0.0f, 1.0f)
    };
    int QTY = sizeof(positions);
    
    ret.size = QTY / sizeof(vec3);
    ret.positions = (vec3*)malloc(QTY);
    memcpy(ret.positions, positions, QTY);

    return ret;
}
