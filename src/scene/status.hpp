//
// Created by syq on 23-7-27.
//

#pragma once

namespace SceneStatus {
    bool blinn = false;

    float previous_time = 0.0f;
    float current_time = 0.0f;
    int fps = 0;

    float flame_radius = 0.1f;
    float flame_lifetime_max = 2.0f;
    float flame_lifetime_min = 1.0f;
    glm::vec3 flame_center = glm::vec3(0.0f);
    glm::vec3 flame_velocity_max = glm::vec3(0.0f, 0.5f, 0.0f);
    glm::vec3 flame_velocity_min = glm::vec3(0.0f, 0.3f, 0.0f);
}
