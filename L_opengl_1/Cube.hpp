#ifndef Cube_hpp
#define Cube_hpp

#include "WorldModel.hpp"
#include "ShapeGenerator.hpp"

class Cube : public WorldModel
{
public:
    Cube(const char* vertexFilePath, const char* fragmentFilePath);
    
    virtual void render() const;
    virtual void clear() const override;

protected:
private:
    GLuint numVertices;
    
    virtual void renderModel() const;
    virtual void renderLight() const override;
    virtual void renderTextures() const override;
};

#endif /* Cube_hpp */
