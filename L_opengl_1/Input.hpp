//
//  Input.hpp
//  L_opengl_1
//
//  Created by apple on 2016-12-15.
//  Copyright © 2016 apple. All rights reserved.
//

#ifndef Input_hpp
#define Input_hpp

#include "includes.h"

class Input
{
public:
    Input(GLFWwindow *window);
    
protected:
    GLFWwindow *window;
    
private:
};

#endif /* Input_hpp */
