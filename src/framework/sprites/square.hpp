//
// Created by chty on 23-6-8.
//
#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <utility>
#include <vector>
#include <memory>
#include "framework/shader.hpp"
#include "framework/sprites/base.hpp"
#include "common/defs.hpp"

class Square: public BaseSprite {
public:
    using BaseSprite::BaseSprite;
    void LoadData() override;
};

void Square::LoadData() {
    this->vertices = {
            -1.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            1.0f,  1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f
    };
    this->indices = { 0,1,2,0,1,3 };
}
