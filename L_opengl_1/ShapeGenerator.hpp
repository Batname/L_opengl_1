#ifndef ShapeGenerator_hpp
#define ShapeGenerator_hpp

#define NUM_ARRAY_ELEMENTS(a, b) sizeof(a) / sizeof(b)

#include "includes.h"
#include "ShapeData.h"
#include "VertexTypes.h"
#include "ObjectsData.h"

class ShapeGenerator
{
private:
public:
    static ShapeData<RegularVertex> makePlane();
    static ShapeData<SimpleVertex> makeLight();
    static ShapeData<VertexPosTexNorm> makeCube();
    static ObjectsData getCubes();
    static ObjectsData getLights();
};

#endif /* ShapeGenerator_hpp */
