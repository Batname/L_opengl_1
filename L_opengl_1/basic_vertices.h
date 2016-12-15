#ifndef basic_vertices_h
#define basic_vertices_h

#include "includes.h"

/*
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
 
GLfloat basic_vertices[] = {
 // first triangle
 0.5f,  0.5f, 0.0f, // Top Right
 0.5f, -0.5f, 0.0f, // Bottom Right
 -0.5f, -0.5f, 0.0f, // Bottom Left
 -0.5f,  0.5f, 0.0f  // Top Left
};
 
GLuint basic_indices[] = {
 0, 1, 3, // first triangle
 1, 2, 3  // second triangle
};
*/

GLfloat basic_vertices[] = {
    // position         // colors
     0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   // Bottom Right
    -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,   // Bottom Left
     0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f    // Top
};

#endif /* basic_vertices_h */
