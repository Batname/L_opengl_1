#ifndef Plane_hpp
#define Plane_hpp

#include "includes.h"

#include "Model.hpp"
#include "ShapeGenerator.hpp"

class Plane : public Model
{
public:
    Plane(const char* vertexFilePath, const char* fragmentFilePath);
    
    virtual void render();
    virtual void clear() const;
protected:
private:
    GLuint planeVAO;
    GLuint planeVBO;
};

#endif /* Plane_hpp */
