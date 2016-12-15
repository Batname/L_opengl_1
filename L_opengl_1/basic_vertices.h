#ifndef basic_vertices_h
#define basic_vertices_h

#include "includes.h"

GLfloat basic_vertices[] = {
    // first triangle
     0.5f,  0.5f, 0.0f, // Top Right
     0.5f, -0.5f, 0.0f, // Bottom Right
    -0.5f,  0.5f, 0.0f, // Top Left
    
    // second triangle
     0.5f, -0.5f, 0.0f, // Bottom Right
    -0.5f, -0.5f, 0.0f, // Bottom Left
    -0.5f,  0.5f, 0.0f  // Top Left
};

#endif /* basic_vertices_h */
