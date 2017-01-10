#include "Camera.hpp"

using namespace glm;

bool Camera::keys[1024] = {};

Camera::Camera(vec3 position, vec3 up, GLfloat yaw, GLfloat pitch) :
    Front({0.0f, 0.0f, -1.0f}),
    MovementSpeed(SPEED),
    MouseSensitivity(SENSITIVITY),
    Zoom(ZOOM),
    Position(position),
    WorldUp(up),
    Yaw(yaw),
    Pitch(pitch)
{
    updateCameraVectors();
}

Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) :
    MovementSpeed(SPEED),
    MouseSensitivity(SENSITIVITY),
    Zoom(ZOOM),
    Position(vec3(posX, posY, posZ)),
    WorldUp(vec3(upX, upY, upZ)),
    Yaw(yaw),
    Pitch(pitch)
{
    updateCameraVectors();
}

mat4 Camera::GetViewMatrix() {
    return lookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(CameraMovement direction, GLfloat deltaTime) {
    GLfloat velocity = MovementSpeed * deltaTime;

    if (direction == FORWARD)
        Position += Front * velocity;
    if (direction == BACKWARD)
        Position -= Front * velocity;
    if (direction == LEFT)
        Position -= Right * velocity;
    if (direction == RIGHT)
        Position += Right * velocity;
    if (direction == UPWARD)
        Position += Up * velocity;
    if (direction == DOWN)
        Position -= Up * velocity;
}

void Camera::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch){
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;
    
    Yaw   += xoffset;
    Pitch += yoffset;
    
    if (constrainPitch) {
        if (Pitch > 89.0f) Pitch = 89.0f;
        if (Pitch < -89.0f) Pitch = -89.0f;
    }
    
    updateCameraVectors();
}

void Camera::ProcessMouseScroll(GLfloat yoffset) {
    if (Zoom >= 1.0f && Zoom <= 45.0f) Zoom -= yoffset;
    if (Zoom <= 1.0f) Zoom = 1.0f;
    if (Zoom >= 45.0f) Zoom = 45.0f;
}

void Camera::DoMovement(GLfloat deltaTime) {
    if(Camera::keys[GLFW_KEY_W])
        ProcessKeyboard(FORWARD, deltaTime);
    if(Camera::keys[GLFW_KEY_S])
        ProcessKeyboard(BACKWARD, deltaTime);
    if(Camera::keys[GLFW_KEY_A])
        ProcessKeyboard(LEFT, deltaTime);
    if(Camera::keys[GLFW_KEY_D])
        ProcessKeyboard(RIGHT, deltaTime);
    if(Camera::keys[GLFW_KEY_R])
        ProcessKeyboard(UPWARD, deltaTime);
    if(Camera::keys[GLFW_KEY_F])
        ProcessKeyboard(DOWN, deltaTime);
}


void Camera::updateCameraVectors() {
    vec3 front;
    front.x = cos(radians(Yaw)) * cos(radians(Pitch));
    front.y = sin(radians(Pitch));
    front.z = sin(radians(Yaw)) * cos(radians(Pitch));
    
    Front = normalize(front);
    
    Right = normalize(cross(Front, WorldUp));
    Up = normalize(cross(Right, Front));
}
