#include "Camera.hpp"

using namespace glm;

bool Camera::keys[1024] = {};
const vec3 Camera::FRONT = vec3(0.0f, 0.0f, -1.0f);
const vec3 Camera::UP = vec3(0.0f, 1.0f,  0.0);
const vec3 Camera::POSITION = vec3(0.0f, 0.0f,  0.0f);

Camera::Camera(vec3 position, vec3 up, GLfloat yaw, GLfloat pitch) :
    Front(Camera::FRONT),
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
    
    myUpdateCameraVectors(xoffset, yoffset);
//    updateCameraVectors();
}

void Camera::myUpdateCameraVectors(GLfloat xoffset, GLfloat yoffset) {
    mat4 rotator, pitch, yaw;
    pitch = rotate(radians(yoffset), Right);
    yaw = rotate(radians(-xoffset), Up);
    rotator = pitch * yaw;

    Front = normalize(mat3(rotator) * Front);
    Right = normalize(cross(Front, Up));
    Up = normalize(cross(Right, Front));
}

void Camera::ProcessMouseScroll(GLfloat yoffset) {
    mat4 roll = rotate(radians(yoffset), cross(Right, Up));
    Up = normalize(mat3(roll) * Up);
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
