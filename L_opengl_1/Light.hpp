#ifndef Light_hpp
#define Light_hpp

#include "Model.hpp"
#include "ShapeGenerator.hpp"
#include "ObjectsData.h"

class Light : public Model
{
public:
    explicit Light(const char* vertexFilePath, const char* fragmentFilePath);

    virtual void render() const;
    virtual void clear();
private:
    GLuint lightVAO;
    GLuint lightVBO;
    GLuint numVertices;
    ObjectsData lightObjects;
    
    void draw() const;
};

#endif /* Light_hpp */
