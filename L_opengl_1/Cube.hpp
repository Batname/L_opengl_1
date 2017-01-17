#ifndef Cube_hpp
#define Cube_hpp

#include "WorldModel.hpp"
#include "ShapeGenerator.hpp"
#include "ObjectsData.h";

class Cube : public WorldModel
{
public:
    Cube(const char* vertexFilePath, const char* fragmentFilePath);
    
    virtual void render() const;
    virtual void clear() override;

protected:
private:
    GLuint numVertices;
    GLuint diffuseMap;
    GLuint specularMap;
    ObjectsData objectsData;
    ObjectsData lightObjects;
    
    virtual void renderModel() const;
    virtual void renderLight() const override;
    virtual void renderTextures() const override;
};

#endif /* Cube_hpp */
