#ifndef WorldModel_hpp
#define WorldModel_hpp

#include "includes.h"
#include "Model.hpp"
#include "ShapeGenerator.hpp"

class WorldModel : public Model
{
public:
    WorldModel(const char* vertexFilePath, const char* fragmentFilePath);
protected:

    virtual void preRender() const;
    virtual void renderLight() const;
    virtual void clear() const;
    virtual void draw() const;
    
    GLuint VAO;
    GLuint VBO;
    GLuint numVertices;

private:
};

#endif /* WorldModel_hpp */
