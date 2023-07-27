//
// Created by chty on 23-7-4.
//

#pragma once
#include <utility>

#include "framework/sprites/base.hpp"

class Floor: public BaseSprite {
public:
    using BaseSprite::BaseSprite;
    void LoadData() override;
};

void Floor::LoadData() {
    for(int i = 0; i < 2; ++i) {
        for(int j = 0; j < 2; ++j) {
            this->vertices.emplace_back(
                    glm::vec3(25.0f * (float)(i * 2 - 1), 0.0f, 25.0f * (float)(j * 2 - 1)),
                    glm::vec2(25.0f * (float)i, 25.0f * (float)j),
                    glm::vec3(0.0f, 1.0f, 0.0f)
                    );
        }
    }
    this->indices = { 0,1,2,1,2,3 };
}
