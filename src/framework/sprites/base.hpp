//
// Created by chty on 23-7-3.
//
#pragma once
#include <GLFW/glfw3.h>
#include "framework/shader.hpp"
#include <common/defs.hpp>

class BaseSprite {
protected:
    Shader shader;
    GLfloatVec vertices;
    GLuintVec indices;
    GLuint vao{}, vbo{}, ebo{};
public:
    explicit BaseSprite(Shader shader);
    virtual ~BaseSprite() = default;
    virtual void LoadData() = 0;
    void LoadBuffer();
    void Draw(glm::vec3 position, glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3 rotate = glm::vec3(0.0f, 0.0f, 0.0f));
};

BaseSprite::BaseSprite(Shader shader) : shader(shader) {}

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
//    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
//    glEnableVertexAttribArray(2);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BaseSprite::Draw(glm::vec3 position, glm::vec3 size, glm::vec3 rotate) {
    auto model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, rotate[0], glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, rotate[1], glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, rotate[2], glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, size);

    this->shader.Use();
    this->shader.SetAttribute("model", model);

    glBindVertexArray(this->vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
    glDrawElements(GL_TRIANGLES, (int)this->indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

