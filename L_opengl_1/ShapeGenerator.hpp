#ifndef ShapeGenerator_hpp
#define ShapeGenerator_hpp

#define NUM_ARRAY_ELEMENTS(a) sizeof(a) / sizeof(*a)

#include "includes.h"
#include "ShapeData.h"
#include "VertexTypes.h"

class ShapeGenerator
{
private:
public:
    static ShapeData<RegularVertex> makePlane();
};

#endif /* ShapeGenerator_hpp */
