//
// Created by syq on 23-7-31.
//

#pragma once
#include "framework/texture_random.hpp"

class ParticleSystem {
private:
    GLuint vao[2] = {};
    GLuint vbo[2] = {};
    GLuint tfo[2] = {};

    int cur = 0;
    shared_ptr<TextureRandom> texture_rd;
    std::string texture;

    void UpdateParticles(shared_ptr<Shader>& shader);
    void RenderParticles(shared_ptr<Shader>& shader);

public:
    ParticleSystem(glm::vec3 position, const std::string& texture);
    ~ParticleSystem();
    void Render(shared_ptr<Shader>& shader_update, shared_ptr<Shader>& shader_render);
};

ParticleSystem::ParticleSystem(glm::vec3 position, const std::string& texture) {
    this->texture_rd = std::make_shared<TextureRandom>(1000);
    this->texture = texture;

    vector<Particle> particles(PARTICLE_NUM);
    particles[0] = {
            .position = glm::vec3(position),
            .velocity = glm::vec3(0.0f, 0.0001f, 0.0f),
            .type = 0,
            .lifetime = 0.0f
    };

    glGenVertexArrays(2, vao);
    glGenTransformFeedbacks(2, tfo);
    glGenBuffers(2, vbo);

    for(int i = 0; i < 2; ++i) {
        glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, tfo[i]);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
        glBufferData(GL_ARRAY_BUFFER, particles.size() * sizeof(Particle), particles.data(), GL_DYNAMIC_DRAW);
        glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, vbo[i]);
    }
}

ParticleSystem::~ParticleSystem() {
    glDeleteTransformFeedbacks(2, tfo);
    glDeleteBuffers(2, vbo);
}

void ParticleSystem::Render(shared_ptr<Shader>& shader_update, shared_ptr<Shader>& shader_render) {
    UpdateParticles(shader_update);
    RenderParticles(shader_render);
    cur ^= 1;
}

void ParticleSystem::UpdateParticles(shared_ptr<Shader>& shader) {
    static double previous_time = 0.0f;
    auto current_time = (float)glfwGetTime();
    auto duration = (float)(current_time - previous_time);
    previous_time = current_time;

    shader->Use();
    shader->SetAttribute("gTime", current_time * 1000);
    shader->SetAttribute("gDeltaTime", duration * 1000);
    this->texture_rd->Bind(0);

    glEnable(GL_RASTERIZER_DISCARD);   //取消光栅化

    glBindVertexArray(vao[cur]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[cur]);
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, tfo[cur^1]);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)(7 * sizeof(float)));
    glEnableVertexAttribArray(3);

    glBeginTransformFeedback(GL_POINTS);
    static bool is_first = true;
    if (is_first) {
        glDrawArrays(GL_POINTS, 0, 1);
        is_first = false;
    } else {
        glDrawTransformFeedback(GL_POINTS, tfo[cur]);
    }
    glEndTransformFeedback();
    glBindVertexArray(0);
}

void ParticleSystem::RenderParticles(shared_ptr<Shader>& shader) {
    shader->Use();
    ResourceManager::BindTexture(this->texture, 0);

    glDisable(GL_RASTERIZER_DISCARD);

    glBindVertexArray(vao[cur^1]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[cur^1]);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)0);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_POINTS, 0, 1);
    glDrawTransformFeedback(GL_POINTS, tfo[cur^1]);
    glBindVertexArray(0);
}
