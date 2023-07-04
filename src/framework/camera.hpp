//
// Created by chty on 23-7-4.
//
#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <common/defs.hpp>

class Camera {
private:
    glm::vec3 camera_pos;
    glm::vec3 camera_front;
    glm::vec3 camera_up;
    glm::vec3 camera_right;
    glm::vec3 world_up;
    float pitch;
    float yaw;
    float zoom;

    void UpdateState();

public:
    Camera(glm::vec3 camera_pos, glm::vec3 world_up, float pitch, float yaw);
    void KeyboardInput(Direction direction, float duration);
    void MouseMove();
    void MouseScroll();
};

Camera::Camera(glm::vec3 camera_pos, glm::vec3 world_up, float pitch, float yaw): camera_pos(camera_pos), world_up(world_up) {
    this->zoom = CAMERA_ZOOM;
    this->yaw = CAMERA_YAW;
    this->pitch = CAMERA_PITCH;
    this->UpdateState();
}

void Camera::UpdateState() {
    this->camera_front.x = cos(this->pitch);
}

void Camera::KeyboardInput(Direction direction, float duration) {
    float distance = CAMERA_SPEED * duration;
    switch (direction) {
        case forward:
            this->camera_pos += this->camera_front * distance; break;
        case backward:
            this->camera_pos -= this->camera_front * distance; break;
        case left:
            this->camera_pos -= this->camera_right * distance; break;
        case right:
            this->camera_pos += this->camera_right * distance; break;
        case up:
            this->camera_pos.y += distance; break;
        case down:
            this->camera_pos.y -= distance; break;
    }
}


