#ifndef Plane_hpp
#define Plane_hpp

#include "includes.h"

#include "Model.hpp"

class Plane : public Model
{
public:
    Plane(const char* vertexFilePath, const char* fragmentFilePath);
    
    void render();
    void clear();
protected:
private:
};

#endif /* Plane_hpp */
