#ifndef Plane_hpp
#define Plane_hpp

#include "includes.h"

#include "WorldModel.hpp"
#include "ShapeGenerator.hpp"

class Plane : public WorldModel
{
public:
    Plane(const char* vertexFilePath, const char* fragmentFilePath);
    
    virtual void render() const;
    virtual void renderModel() const;
    virtual void clear() const override ;
protected:
private:
    GLuint numVertices;
};

#endif /* Plane_hpp */
