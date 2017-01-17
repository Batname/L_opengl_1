#ifndef WorldModel_hpp
#define WorldModel_hpp

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
    
    virtual void renderTextures() const;
    virtual void loadTextures(char* texturePath);
    
    GLuint VAO;
    GLuint VBO;
    GLuint numVertices;
    GLuint diffuseMap;

private:
};

#endif /* WorldModel_hpp */
