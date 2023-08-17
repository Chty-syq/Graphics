//
// Created by syq on 23-7-27.
//

#pragma once

namespace SceneStatus {
    bool blinn = false;

    float previous_time = -1.0f;
    float current_time = 0.0f;
    int fps = 0;

    //火焰参数
    float flame_radius = 0.1f;
    float flame_lifetime_max = 2.0f;
    float flame_lifetime_min = 1.0f;
    glm::vec3 flame_center = glm::vec3(0.0f);
    glm::vec3 flame_velocity_max = glm::vec3(0.0f, 0.5f, 0.0f);
    glm::vec3 flame_velocity_min = glm::vec3(0.0f, 0.3f, 0.0f);

    //喷泉参数
    float fountain_radius = 0.01f;
    float fountain_theta = glm::radians(120.0f);
    float fountain_lifetime_max = 1.0f;
    float fountain_lifetime_min = 0.3f;

    float GetDuration() {
        return previous_time < 0.0f ? 0.0f : current_time - previous_time;
    }
}
