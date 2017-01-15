#ifndef Model_hpp
#define Model_hpp

class Model
{
public:
    explicit Model(const char* vertexFilePath, const char* fragmentFilePath);
protected:
private:
    const char* vertexFilePath;
    const char* fragmentFilePath;
};

#endif /* Model_hpp */
