//
// Created by syq on 23-8-2.
//

#pragma once

struct Fireworks {
    glm::vec3   position;
    glm::vec3   velocity;
    glm::vec4   color;
    GLfloat     type;
    GLfloat     lifetime;
    GLfloat     tag;
    static vector<Fireworks> GetLaunchers();
    static void BindUpdateVAO();
    static void BindRenderVAO();
};

vector<Fireworks> Fireworks::GetLaunchers() {
    vector<Fireworks> launchers;
    launchers.push_back({
        .position = glm::vec3(0.0f),
        .velocity = glm::vec3(0.0f, 0.01f, 0.0f),
        .color = glm::vec4(0.5f, 0.3f, 0.1f, 1.0f),
        .type = 0,
        .lifetime = 0.0f,
        .tag = 0.0f
    });
    return launchers;
}

void Fireworks::BindUpdateVAO() {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Fireworks), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Fireworks), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Fireworks), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Fireworks), (void*)(10 * sizeof(float)));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(Fireworks), (void*)(11 * sizeof(float)));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(5, 1, GL_FLOAT, GL_FALSE, sizeof(Fireworks), (void*)(12 * sizeof(float)));
    glEnableVertexAttribArray(5);
}

void Fireworks::BindRenderVAO() {
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Fireworks), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Fireworks), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(1);
}
