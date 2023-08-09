//
// Created by syq on 23-7-10.
//
#pragma once
#include <utility>

#include "framework/sprites/base.hpp"
#include "framework/model/model.hpp"

template<typename T> class GameObject {
private:
    shared_ptr<T> graph;
public:
    glm::vec3 position;
    glm::vec3 size;
    glm::vec3 rotate;
    bool active;  //是否显示
    GameObject(
            shared_ptr<T> graph,
            glm::vec3 position,
            glm::vec3 size = glm::vec3(1.0f),
            glm::vec3 rotate = glm::vec3(0.0f)
            );
    void Draw(shared_ptr<Shader>& shader);
};

template<typename T> GameObject<T>::GameObject(shared_ptr<T> graph, glm::vec3 position, glm::vec3 size, glm::vec3 rotate): position(position), size(size), rotate(rotate), active(true) {
    this->graph = graph;
    if constexpr (std::is_same_v<BaseSprite, T>) {
        this->graph->LoadData();
        this->graph->LoadBuffer();
    }
}

template<typename T> void GameObject<T>::Draw(shared_ptr<Shader> &shader) {
    if (!this->active)  return;
    this->graph->Draw(shader, position, size, rotate);
}

