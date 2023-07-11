//
// Created by syq on 23-7-10.
//
#pragma once
#include <utility>
#include "framework/sprites/base.hpp"
#include "common/defs.hpp"

class Sphere: public BaseSprite {
public:
    using BaseSprite::BaseSprite;
    void LoadData() override;

    static const int rows = 30;
    static const int cols = 40;
};

void Sphere::LoadData() {
    for(int i = 0; i <= rows; ++i) {
        for(int j = 0; j <= cols; ++j) {
            float fhi = 1.0f * PI * (GLfloat)i / (GLfloat)rows;
            float phi = 2.0f * PI * (GLfloat)j / (GLfloat)cols;
            this->vertices.insert(this->vertices.end(), {
                sin(fhi) * cos(phi),
                cos(fhi),
                sin(fhi) * sin(phi),
                (GLfloat)i / (GLfloat)rows,
                (GLfloat)j / (GLfloat)cols,
                sin(fhi) * cos(phi),
                cos(fhi),
                sin(fhi) * sin(phi),
            });
            if (i == rows || j == cols) continue;
            this->indices.insert(this->indices.end(), {
                (GLuint)i * (cols + 1) + j,
                (GLuint)i * (cols + 1) + j + 1,
                (GLuint)(i + 1) * (cols + 1) + j,
                (GLuint)i * (cols + 1) + j + 1,
                (GLuint)(i + 1) * (cols + 1) + j + 1,
                (GLuint)(i + 1) * (cols + 1) + j
            });
        }
    }
}
