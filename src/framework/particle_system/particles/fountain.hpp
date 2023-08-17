//
// Created by syq on 23-8-16.
//

#pragma once
#include "scene/status.hpp"
#include <random>

struct Fountain {
    glm::vec3 position;
    glm::vec3 velocity;
    float type;
    float lifetime;
    static vector<Fountain> GetLaunchers();
    static void BindUpdateVAO();
    static void BindRenderVAO();
};

vector<Fountain> Fountain::GetLaunchers() {
    vector<Fountain> launchers;
    std::normal_distribution<float> dist(0, SceneStatus::flame_radius);
    for(int i = 0; i < 1500; ++i) {
        float theta = utils::RandomFloat(0, 2 * PI);
        float r = sqrt(utils::RandomFloat(0, pow(SceneStatus::fountain_radius, 2.0f)));
        launchers.push_back({
            .position = glm::vec3(r * cos(theta), 0.0f, r * sin(theta)),
            .velocity = glm::vec3(0.0f),
            .type = 0.0f,
            .lifetime = (SceneStatus::fountain_lifetime_max - SceneStatus::fountain_lifetime_min) * utils::RandomFloat(0.0f, 1.0f) + SceneStatus::fountain_lifetime_min
        });
    }
    return launchers;
}

void Fountain::BindUpdateVAO() {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Fountain), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Fountain), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Fountain), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Fountain), (void*)(7 * sizeof(float)));
    glEnableVertexAttribArray(3);
}

void Fountain::BindRenderVAO() {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Fountain), (void*)0);
    glEnableVertexAttribArray(0);
}
