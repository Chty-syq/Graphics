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
    explicit Camera(glm::vec3 camera_pos);
    auto GetViewMat();
    auto GetZoom() const;
    void KeyboardInput(Direction direction, float duration);
    void MouseMove(float offset_x, float offset_y);
    void MouseScroll(float offset);
};

Camera::Camera(glm::vec3 camera_pos): camera_pos(camera_pos) {
    this->zoom = CAMERA_ZOOM;
    this->yaw = CAMERA_YAW;
    this->pitch = CAMERA_PITCH;
    this->world_up = glm::vec3(0.0f, 1.0f, 0.0f);
    this->UpdateState();
}

void Camera::UpdateState() {
    camera_front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    camera_front.y = sin(glm::radians(pitch));
    camera_front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    camera_front = glm::normalize(camera_front);
    camera_right = glm::normalize(glm::cross(camera_front, world_up));
    camera_up = glm::normalize(glm::cross(camera_right, camera_front));
}

void Camera::KeyboardInput(Direction direction, float duration) {
    float distance = CAMERA_SPEED * duration;
    switch (direction) {
        case forward:
            camera_pos += camera_front * distance; break;
        case backward:
            camera_pos -= camera_front * distance; break;
        case left:
            camera_pos -= camera_right * distance; break;
        case right:
            camera_pos += camera_right * distance; break;
        case up:
            camera_pos.y += distance; break;
        case down:
            camera_pos.y -= distance; break;
    }
}

void Camera::MouseMove(float offset_x, float offset_y) {
    yaw += offset_x * CAMERA_SENSITIVITY;
    pitch += offset_y * CAMERA_SENSITIVITY;
    pitch = std::min(pitch, 89.0f);
    pitch = std::max(pitch, -89.0f);
    this->UpdateState();
}

void Camera::MouseScroll(float offset) {
    zoom -= offset;
    zoom = std::max(zoom, 1.0f);
    zoom = std::min(zoom, 45.0f);
}

auto Camera::GetViewMat() {
    return glm::lookAt(camera_pos, camera_pos + camera_front, camera_up);
}

auto Camera::GetZoom() const {
    return this->zoom;
}


