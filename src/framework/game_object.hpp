//
// Created by syq on 23-7-10.
//
#pragma once
#include <utility>

#include "framework/sprites/base.hpp"
#include "framework/model/model.hpp"

class GameObject {
private:
    GameObjectType type;
    shared_ptr<BaseSprite> sprite;
    shared_ptr<Model> model;
public:
    glm::vec3 position;
    glm::vec3 size;
    glm::vec3 rotate;
    bool active;  //是否显示
    GameObject(
            shared_ptr<BaseSprite> sprite,
            glm::vec3 position,
            glm::vec3 size = glm::vec3(1.0f),
            glm::vec3 rotate = glm::vec3(0.0f)
            );
    GameObject(
            shared_ptr<Model> model,
            glm::vec3 position,
            glm::vec3 size = glm::vec3(1.0f),
            glm::vec3 rotate = glm::vec3(0.0f)
            );
    void Draw(shared_ptr<Shader>& shader);
};

GameObject::GameObject(shared_ptr<BaseSprite> sprite, glm::vec3 position, glm::vec3 size, glm::vec3 rotate): position(position), size(size), rotate(rotate) {
    this->type = GameObjectType::sprite;
    this->active = true;
    this->sprite = std::move(sprite);
    this->sprite->LoadData();
    this->sprite->LoadBuffer();
}

GameObject::GameObject(shared_ptr<Model> model, glm::vec3 position, glm::vec3 size, glm::vec3 rotate): position(position), size(size), rotate(rotate) {
    this->type = GameObjectType::model;
    this->active = true;
    this->model = std::move(model);
}

void GameObject::Draw(shared_ptr<Shader> &shader) {
    if(!this->active)  return;
    switch (this->type) {
        case ::sprite: this->sprite->Draw(shader, position, size, rotate); break;
        case ::model: this->model->Draw(shader, position, size, rotate); break;
    }
}

