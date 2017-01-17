#ifndef ObjectsData_h
#define ObjectsData_h

using namespace glm;

struct ObjectsData
{
    ObjectsData() : positions(nullptr), size(0) {}
    
    GLuint size;
    vec3* positions;
    
    void clean()
    {
        free(positions);
        size = 0;
    }
};

#endif /* ObjectsData_h */
