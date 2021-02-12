//
// Created by nicola on 12/02/2021.
//

#include "Camera.h"
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
    //TODO vectors
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
    //TODO vectors
}
