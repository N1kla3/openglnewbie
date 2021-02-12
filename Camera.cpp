//
// Created by nicola on 12/02/2021.
//

#include "Camera.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : position(position),
      up(up),
      yaw(yaw),
      pitch(pitch),
      front(glm::vec3(0.f, 0.f, -1.f)),
      movement_speed(SPEED),
      mouse_sensitivity(SENSITIVITY),
      zoom(ZOOM)
{
    UpdateCameraVectors();
}
Camera::Camera(float posx, float posy, float posz, float upx, float upy, float upz, float yaw, float pitch)
    : position(posx, posy, posz),
      up(upx, upy, upz),
      yaw(yaw),
      pitch(pitch),
      front(glm::vec3(0.f, 0.f, -1.f)),
      movement_speed(SPEED),
      mouse_sensitivity(SENSITIVITY),
      zoom(ZOOM)
{
    UpdateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix() const
{
    return glm::lookAt(position, position + front, up);
}

void Camera::ProcessKeyboard(CAMERA_MOVEMENT direction, float deltaTime)
{
    float velocity = deltaTime * movement_speed;
    if (direction == CAMERA_MOVEMENT::MOVE_FORWARD)
        position += front * velocity;
    if (direction == CAMERA_MOVEMENT::MOVE_BACK)
        position -= front * velocity;
    if (direction == CAMERA_MOVEMENT::MOVE_LEFT)
        position -= right * velocity;
    if (direction == CAMERA_MOVEMENT::MOVE_RIGHT)
        position += right * velocity;
}

void Camera::ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch)
{
    xOffset *= mouse_sensitivity;
    yOffset *= mouse_sensitivity;

    yaw += xOffset;
    pitch += yOffset;

    if (constrainPitch)
    {
        if (pitch > 89.f)
            pitch = 89.f;
        if (pitch < -89.f)
            pitch = -89.f;
    }
    UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(float yOffset)
{
    zoom -= yOffset;
    if (zoom < 1.f)
        zoom = 1.f;
    if (zoom > 45.f)
        zoom = 45.f;
}

void Camera::UpdateCameraVectors()
{
    glm::vec3 _front(1.f);
    _front.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    _front.y = glm::sin(glm::radians(pitch));
    _front.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
    front = glm::normalize(_front);

    right = glm::normalize(glm::cross(front, world_up));
    up = glm::normalize(glm::cross(right, front));
}