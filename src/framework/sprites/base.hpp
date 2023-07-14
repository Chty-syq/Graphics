//
// Created by chty on 23-7-3.
//
#pragma once
#include <GLFW/glfw3.h>
#include "framework/shader.hpp"
#include "scene/resources.hpp"
#include <common/defs.hpp>
#include <utility>
#include <numeric>

class BaseSprite {
protected:
    GLfloatVec vertices;
    GLuintVec indices;
    GLuint vao{}, vbo{}, ebo{};
    std::string diffuse_map = "empty";
    std::string specular_map = "empty";
    void Combine(const BaseSprite& other);
    void Combine(const GLfloatVec& o_vertices, const GLuintVec& o_indices);
public:
    BaseSprite() = default;
    explicit BaseSprite(const std::string &diffuse_map);
    BaseSprite(const std::string &diffuse_map, const std::string &specular_map);
    ~BaseSprite();
    virtual void LoadData() = 0;
    void LoadBuffer();
    void Render() const;  //渲染
    void Draw(
        shared_ptr<Shader>& shader,
        glm::vec3 position,
        glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3 rotate = glm::vec3(0.0f, 0.0f, 0.0f)
    );
};

BaseSprite::BaseSprite(const std::string &diffuse_map) {
    this->diffuse_map = diffuse_map;
}

BaseSprite::BaseSprite(const std::string &diffuse_map, const std::string &specular_map) {
    this->diffuse_map = diffuse_map;
    this->specular_map = specular_map;
}

BaseSprite::~BaseSprite() {
    glDeleteVertexArrays(1, &this->vao);
    glDeleteBuffers(1, &this->vbo);
    glDeleteBuffers(1, &this->ebo);
}

void BaseSprite::Combine(const BaseSprite &other) {
    this->Combine(other.vertices, other.indices);
}

void BaseSprite::Combine(const GLfloatVec &o_vertices, const GLuintVec& o_indices) {
    int offset = (int)this->vertices.size() / 8;
    for(auto & index : o_indices) {
        this->indices.push_back(index + offset);
    }
    this->vertices.insert(this->vertices.end(), o_vertices.begin(), o_vertices.end());
}

void BaseSprite::LoadBuffer() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLfloat), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BaseSprite::Render() const {
    glBindVertexArray(this->vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
    glDrawElements(GL_TRIANGLES, (int)this->indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void BaseSprite::Draw(shared_ptr<Shader>& shader, glm::vec3 position, glm::vec3 size, glm::vec3 rotate) {
    auto model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, rotate[0], glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, rotate[1], glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, rotate[2], glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, size);

    shader->Use();
    shader->SetAttribute("model", model);

    ResourceManager::BindTexture(this->diffuse_map, 0);
    ResourceManager::BindTexture(this->specular_map, 1);

    this->Render();
}
