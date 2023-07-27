//
// Created by chty on 23-6-8.
//
#pragma once
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
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
    for(int i = 0; i < 2; ++i) {
        for(int j = 0; j < 2; ++j) {
            this->vertices.emplace_back(
                    glm::vec3(1.0f * (float)(i * 2 - 1), 1.0f * (float)(j * 2 - 1), 0.0f),
                    glm::vec2(1.0f * (float)i, 1.0f * (float)j),
                    glm::vec3(0.0f, 0.0f, 1.0f)
            );
        }
    }
    this->indices = { 0,1,2,1,2,3 };
}
