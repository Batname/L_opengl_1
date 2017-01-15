#ifndef ShapeGenerator_hpp
#define ShapeGenerator_hpp

#define NUM_ARRAY_ELEMENTS(a, b) sizeof(a) / sizeof(b)

#include "includes.h"
#include "ShapeData.h"
#include "VertexTypes.h"

class ShapeGenerator
{
private:
public:
    static ShapeData<RegularVertex> makePlane();
    static ShapeData<SimpleVertex> makeLight();
};

#endif /* ShapeGenerator_hpp */
