#ifndef Camera_hpp
#define Camera_hpp

#include <vector>

#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>

using namespace glm;

class Camera {
    enum CameraMovement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UPWARD,
        DOWN
    };
    
public:
    constexpr static GLfloat YAW            = -90.0f;
    constexpr static GLfloat PITCH          =  0.0f;
    constexpr static GLfloat SPEED          =  3.0f;
    constexpr static GLfloat SENSITIVITY    =  0.25f;
    constexpr static GLfloat ZOOM           =  45.0f;
    
    const static vec3 FRONT;
    const static vec3 UP;
    const static vec3 POSITION;

    static bool keys[1024];
    
    explicit Camera(
        vec3 position = POSITION,
        vec3 up = UP,
        GLfloat yaw = YAW,
        GLfloat pitch = PITCH
    );
    
    explicit Camera(
        GLfloat posX,
        GLfloat posY,
        GLfloat posZ,
        GLfloat upX,
        GLfloat upY,
        GLfloat upZ,
        GLfloat yaw,
        GLfloat pitch
    );
    
    mat4 GetViewMatrix();
    void ProcessKeyboard(CameraMovement direction, GLfloat deltaTime);
    void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true);
    void ProcessMouseScroll(GLfloat yoffset);
    
    void DoMovement(GLfloat deltaTime);
    
private:
    vec3 Position;
    vec3 Front;
    vec3 Up;
    vec3 Right;
    vec3 WorldUp;
    
    GLfloat Yaw;
    GLfloat Pitch;

    GLfloat MovementSpeed;
    GLfloat MouseSensitivity;
    GLfloat Zoom;
    
    void updateCameraVectors();
};

#endif /* Camera_hpp */
