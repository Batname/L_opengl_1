#ifndef Camera_hpp
#define Camera_hpp

#include "includes.h"

using namespace glm;

class Camera {
    friend class Game;
    
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
    
    const mat4& GetViewMatrix() const;
    const mat4& GetProjection() const;
    const vec3& GetFront() const;
    const vec3* GetPosition() const;

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
    GLfloat Roll;
    
    GLfloat xoffset;
    GLfloat yoffset;
    
    void updateCameraVectors();
    void myUpdateCameraVectors();

};

#endif /* Camera_hpp */
