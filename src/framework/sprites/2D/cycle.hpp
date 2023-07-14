//
// Created by syq on 23-7-14.
//

#pragma once
#include <utility>

#include "framework/sprites/base.hpp"

class Cycle: public BaseSprite {
public:
    using BaseSprite::BaseSprite;
    void LoadData() override;
private:
    static const int nums = 30;
};

void Cycle::LoadData() {
    for(int i = 0; i <= nums; ++i) {
        float theta = 2.0f * PI * (GLfloat)i / (GLfloat)nums;
        this->vertices.insert(this->vertices.end(), {
            cos(theta),
            0.0f,
            sin(theta),
            cos(theta) / 2 + 0.5f,
            sin(theta) / 2 + 0.5f,
            0.0f,
            1.0f,
            0.0f
        });
        if (i == nums) continue;
        this->indices.insert(this->indices.end(), {
            (GLuint)i,
            (GLuint)i + 1,
            (GLuint)nums + 1
        });
    }
    this->vertices.insert(this->vertices.end(), { //中心点
        0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f
    });
}
