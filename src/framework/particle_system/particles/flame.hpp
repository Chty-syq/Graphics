//
// Created by syq on 23-8-3.
//

#pragma once
#include "scene/status.hpp"
#include <random>

struct Flame {
    glm::vec3 position;
    glm::vec3 velocity;
    float alpha;
    float type;
    float size;
    float lifetime;
    float lifespan;
    static vector<Flame> GetLaunchers();
    static void BindUpdateVAO();
    static void BindRenderVAO();
};

vector<Flame> Flame::GetLaunchers() {
    vector<Flame> launchers;
    std::normal_distribution<float> dist(0, 0.1f);
    for(int i = 0; i < 10000; ++i) {
        launchers.push_back({
            .position = glm::vec3(dist(utils::generator()), 0.0f, dist(utils::generator())),
            .velocity = glm::vec3(0.0f),
            .alpha = 1.0f,
            .type = 0.0f,
            .size = 0.05f,
            .lifetime = 0.0f,
            .lifespan = (SceneStatus::flame_lifetime_max - SceneStatus::flame_lifetime_min) * utils::RandomFloat(0.0f, 1.0f) + SceneStatus::flame_lifetime_min
        });
    }
    return launchers;
}

void Flame::BindUpdateVAO() {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Flame), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Flame), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Flame), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Flame), (void*)(7 * sizeof(float)));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(Flame), (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, sizeof(Flame), (void*)(9 * sizeof(float)));
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(6, 1, GL_FLOAT, GL_FALSE, sizeof(Flame), (void*)(10 * sizeof(float)));
    glEnableVertexAttribArray(6);
}

void Flame::BindRenderVAO() {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Flame), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(Flame), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Flame), (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Flame), (void*)(9 * sizeof(float)));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(Flame), (void*)(10 * sizeof(float)));
    glEnableVertexAttribArray(4);
}
