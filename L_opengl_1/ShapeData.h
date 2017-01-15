#ifndef ShapeData_h
#define ShapeData_h

template <class T>
struct ShapeData
{
    ShapeData() : vertices(nullptr), numVertices(0) {}
    
    T *vertices;
    GLuint numVertices;
    
    GLuint vertexBufferSize() const
    {
        return numVertices * sizeof(T);
    }
    
    GLint getStride() const
    {
        return sizeof(T);
    }
    
    GLvoid* getOffsetPointer(int size, int offset) const
    {
        return (GLvoid*)(size * offset * sizeof(GLfloat));
    }
    
    void clean()
    {
        free(vertices);
        numVertices = 0;
    }
};

#endif /* ShapeData_h */
