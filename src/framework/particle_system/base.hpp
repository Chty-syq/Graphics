//
// Created by syq on 23-7-31.
//

#pragma once
#include "framework/texture_random.hpp"
#include "framework/particle_system/particles/fireworks.hpp"
#include "framework/particle_system/particles/flame.hpp"

template<typename T> class ParticleSystem {
private:
    GLuint vao[2] = {};
    GLuint vbo[2] = {};
    GLuint tfo[2] = {};

    int cur = 0;
    int num_launchers{};
    shared_ptr<TextureRandom> texture_rd;
    std::string texture;

    void UpdateParticles(shared_ptr<Shader>& shader);
    void RenderParticles(shared_ptr<Shader>& shader);

public:
    ParticleSystem(glm::vec3 position, const std::string& texture);
    ~ParticleSystem();
    void Render(shared_ptr<Shader>& shader_update, shared_ptr<Shader>& shader_render);
};

template<typename T> ParticleSystem<T>::ParticleSystem(glm::vec3 position, const std::string& texture) {
    this->texture_rd = std::make_shared<TextureRandom>(1000);
    this->texture = texture;

    vector<T> particles = T::GetLaunchers(position);
    this->num_launchers = particles.size();
    particles.resize(PARTICLE_NUM);

    glGenVertexArrays(2, vao);
    glGenTransformFeedbacks(2, tfo);
    glGenBuffers(2, vbo);

    for(int i = 0; i < 2; ++i) {
        glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, tfo[i]);
        glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
        glBufferData(GL_ARRAY_BUFFER, particles.size() * sizeof(T), particles.data(), GL_DYNAMIC_DRAW);
        glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, vbo[i]);
    }
}

template<typename T> ParticleSystem<T>::~ParticleSystem() {
    glDeleteTransformFeedbacks(2, tfo);
    glDeleteBuffers(2, vbo);
}

template<typename T> void ParticleSystem<T>::Render(shared_ptr<Shader>& shader_update, shared_ptr<Shader>& shader_render) {
    UpdateParticles(shader_update);
    RenderParticles(shader_render);
    cur ^= 1;
}

template<typename T> void ParticleSystem<T>::UpdateParticles(shared_ptr<Shader>& shader) {
    shader->Use();
    this->texture_rd->Bind(0);

    glEnable(GL_RASTERIZER_DISCARD);   //取消光栅化

    glBindVertexArray(vao[cur]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[cur]);
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, tfo[cur^1]);

    T::BindUpdateVAO();

    glBeginTransformFeedback(GL_POINTS);
    static bool is_first = true;
    if (is_first) {
        glDrawArrays(GL_POINTS, 0, this->num_launchers);
        is_first = false;
    } else {
        glDrawTransformFeedback(GL_POINTS, tfo[cur]);
    }
    glEndTransformFeedback();
    glBindVertexArray(0);
}

template<typename T> void ParticleSystem<T>::RenderParticles(shared_ptr<Shader>& shader) {
    shader->Use();
    ResourceManager::BindTexture(this->texture, 0);

    glDisable(GL_RASTERIZER_DISCARD);

    glBindVertexArray(vao[cur^1]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[cur^1]);

    T::BindRenderVAO();

    glDrawArrays(GL_POINTS, 0, 1);
    glDrawTransformFeedback(GL_POINTS, tfo[cur^1]);
    glBindVertexArray(0);
}
