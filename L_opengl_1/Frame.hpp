
#ifndef Frame_hpp
#define Frame_hpp

#include "includes.h"

class Frame
{
public:
    void calculateFrame();
    GLfloat getDeltaTime();
private:
    GLfloat deltaTime = 0.0f;
    GLfloat lastFrame = 0.0f;
};

#endif /* Frame_hpp */
