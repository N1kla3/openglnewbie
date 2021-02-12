//
// Created by nicola on 12/02/2021.
//

#pragma once

#include <glm/vec3.hpp>

enum CAMERA_MOVEMENT
{
    MOVE_FORWARD,
    MOVE_BACK,
    MOVE_RIGHT,
    MOVE_LEFT
};

constexpr float YAW = 90.f;
constexpr float PITCH = 0.f;
constexpr float SPEED = 2.5f;
constexpr float SENSITIVITY = 0.1f;
constexpr float ZOOM = 45.f;

/** Default camera class */
class Camera
{
public:
    Camera(glm::vec3 position = glm::vec3(0.f, 0.f, 0.f),
           glm::vec3 up = glm::vec3(0.f, 1.f, 0.f),
           float yaw = YAW, float pitch = PITCH);
    Camera(float posx, float posy, float posz,
           float upx, float upy, float upz,
           float yaw  = YAW, float pitch = PITCH);

    virtual ~Camera() = default;

    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 world_up;

    float yaw;
    float pitch;

    float movement_speed;
    float mouse_sensitivity;
    float zoom;
protected:
private:
};
