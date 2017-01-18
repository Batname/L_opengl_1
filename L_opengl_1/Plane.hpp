#ifndef Plane_hpp
#define Plane_hpp

#include "WorldModel.hpp"
#include "ShapeGenerator.hpp"
#include "ObjectsData.h"

class Plane : public WorldModel
{
public:
    Plane(const char* vertexFilePath, const char* fragmentFilePath);
    
    virtual void render() const;
    virtual void clear() override ;
protected:
private:
    virtual void renderModel() const;
    virtual void renderLight() const override;
    
    GLuint numVertices;
    ObjectsData lightObjects;
};

#endif /* Plane_hpp */
