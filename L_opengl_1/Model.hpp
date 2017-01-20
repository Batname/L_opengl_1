#ifndef Model_hpp
#define Model_hpp

#include "ShaderLoader.hpp"

class Model
{
public:
    explicit Model(const char* vertexFilePath, const char* fragmentFilePath);
    
protected:
    ShaderLoader shader;
    
    virtual void preRender() const;
private:
    
};

#endif /* Model_hpp */
