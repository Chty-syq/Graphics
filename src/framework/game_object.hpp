//
// Created by syq on 23-7-10.
//
#pragma once
#include <utility>

#include "framework/sprites/base.hpp"
#include "framework/model/model.hpp"
#include "framework/particle_system/base.hpp"

template<typename T> class GameObject {
private:
    shared_ptr<T> graph;
public:
    glm::vec3 position;
    glm::quat rotate;
    glm::vec3 size;
    bool active;  //是否显示
    GameObject(
            shared_ptr<T> graph,
            glm::vec3 position,
            glm::quat rotate = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
            glm::vec3 size = glm::vec3(1.0f)
            );
    void Render(shared_ptr<Shader>& shader);
    void Render(shared_ptr<Shader>& shader1, shared_ptr<Shader>& shader2);
};

template<typename T> GameObject<T>::GameObject(shared_ptr<T> graph, glm::vec3 position, glm::quat rotate, glm::vec3 size): position(position), size(size), rotate(rotate), active(true) {
    this->graph = graph;
    if constexpr (std::is_base_of_v<BaseSprite, T>) {
        this->graph->LoadData();
        this->graph->LoadBuffer();
    }
}

template<typename T> void GameObject<T>::Render(shared_ptr<Shader> &shader) {
    if (!this->active)  return;
    this->graph->Render(shader, position, rotate, size);
}

template<typename T>
void GameObject<T>::Render(shared_ptr<Shader> &shader1, shared_ptr<Shader> &shader2) {
    if (!this->active)  return;
    this->graph->Render(shader1, shader2, position, rotate, size);
}
