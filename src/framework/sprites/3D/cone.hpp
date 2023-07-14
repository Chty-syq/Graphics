//
// Created by syq on 23-7-14.
//
#pragma once
#include <utility>
#include "framework/sprites/base.hpp"
#include "common/defs.hpp"

class Cone: public BaseSprite { //圆锥体
public:
    using BaseSprite::BaseSprite;
    void LoadData() override;
private:
    static const int rows = 30;
    static const int cols = 60;
};

void Cone::LoadData() {
    for(int i = 0; i <= rows; ++i) {
        for(int j = 0; j <= cols; ++j) {
            float theta = 2.0f * PI * (GLfloat)j / (GLfloat)cols;
            float r = 1.0f - (GLfloat)i / (GLfloat)rows;
            this->vertices.insert(this->vertices.end(), {
                    r * cos(theta),
                    (GLfloat)i / (GLfloat)rows,
                    r * sin(theta),
                    (GLfloat)i / (GLfloat)rows,
                    (GLfloat)j / (GLfloat)cols,
                    sqrt(2.0f) / 2.0f * cos(theta),
                    sqrt(2.0f) / 2.0f,
                    sqrt(2.0f) / 2.0f * sin(theta)
            });
            if (i == rows || j == cols) continue;
            this->indices.insert(this->indices.end(), {
                    (GLuint)i * (cols + 1) + j,
                    (GLuint)i * (cols + 1) + j + 1,
                    (GLuint)(i + 1) * (cols + 1) + j,
                    (GLuint)i * (cols + 1) + j + 1,
                    (GLuint)(i + 1) * (cols + 1) + j ,
                    (GLuint)(i + 1) * (cols + 1) + j + 1
            });
        }
    }

    GLfloatVec cycle_vertices[2] = {};
    GLuintVec cycle_indices[2] = {};
    for(int j = 0; j <= cols; ++j) {
        float theta = 2.0f * PI * (GLfloat)j / (GLfloat)cols;
        cycle_vertices[0].insert(cycle_vertices[0].end(), {
                cos(theta),
                0.0f,
                sin(theta),
                cos(theta) / 2 + 0.5f,
                sin(theta) / 2 + 0.5f,
                0.0f,
                -1.0f,
                0.0f
        });
        if (j == cols) continue;
        cycle_indices[0].insert(cycle_indices[0].end(), {
                (GLuint)j,
                (GLuint)j + 1,
                (GLuint)cols + 1
        });
    }
    cycle_vertices[0].insert(cycle_vertices[0].end(), { 0.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.0f, -1.0f, 0.0f });
    this->Combine(cycle_vertices[0], cycle_indices[0]);  //bottom
}
