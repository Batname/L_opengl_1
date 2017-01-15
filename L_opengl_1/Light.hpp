#ifndef Light_hpp
#define Light_hpp

#include "Model.hpp"
#include "includes.h"
#include "ShapeGenerator.hpp"

class Light : public Model
{
public:
    explicit Light(const char* vertexFilePath, const char* fragmentFilePath);

    virtual void render() const;
    virtual void clear() const;
private:
    GLuint lightVAO;
    GLuint lightVBO;
    GLuint numVertices;
};

#endif /* Light_hpp */
