//
// Created by chty on 23-6-8.
//
#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "framework/shader.hpp"
#include "framework/sprites/base.hpp"

class Square: public BaseSprite {
public:
    explicit Square(Shader shader);
    ~Square() override = default;
    void LoadData() override;
};

Square::Square(Shader shader): BaseSprite(shader) {}

void Square::LoadData() {
    this->vertices = {
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f
    };
    this->indices = { 0,1,2,0,1,3 };
}
