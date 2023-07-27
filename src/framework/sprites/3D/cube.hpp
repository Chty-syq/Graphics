//
// Created by chty on 23-7-4.
//
#pragma once
#include "framework/sprites/base.hpp"
#include <utility>

class Cube: public BaseSprite { //立方体
public:
    using BaseSprite::BaseSprite;
    void LoadData() override;
};

void Cube::LoadData() {
    VertexArr square_vertices[6];
    IndiceArr square_indices[6];
    for(int i = 0; i < 2; ++i) {
        for(int j = 0; j < 2; ++j) {
            square_vertices[0].emplace_back(
                    glm::vec3(0.5f * (float)(i * 2 - 1), 0.5f * (float)(j * 2 - 1), -0.5f),
                    glm::vec2(1.0f * (float)i, 1.0f * (float)j),
                    glm::vec3(0.0f, 0.0f, -1.0f)
                    );
            square_vertices[1].emplace_back(
                    glm::vec3(0.5f * (float)(i * 2 - 1), 0.5f * (float)(j * 2 - 1), 0.5f),
                    glm::vec2(1.0f * (float)i, 1.0f * (float)j),
                    glm::vec3(0.0f, 0.0f, 1.0f)
                    );
            square_vertices[2].emplace_back(
                    glm::vec3(-0.5f, 0.5f * (float)(i * 2 - 1), -0.5f * (float)(j * 2 - 1)),
                    glm::vec2(1.0f * (float)i, 1.0f * (float)j),
                    glm::vec3(-1.0f, 0.0f, 0.0f)
            );
            square_vertices[3].emplace_back(
                    glm::vec3(0.5f, 0.5f * (float)(i * 2 - 1), -0.5f * (float)(j * 2 - 1)),
                    glm::vec2(1.0f * (float)i, 1.0f * (float)j),
                    glm::vec3(1.0f, 0.0f, 0.0f)
            );
            square_vertices[4].emplace_back(
                    glm::vec3(0.5f * (float)(i * 2 - 1), -0.5f, -0.5f * (float)(j * 2 - 1)),
                    glm::vec2(1.0f * (float)i, 1.0f * (float)j),
                    glm::vec3(0.0f, -1.0f, 0.0f)
            );
            square_vertices[5].emplace_back(
                    glm::vec3(0.5f * (float)(i * 2 - 1), 0.5f, -0.5f * (float)(j * 2 - 1)),
                    glm::vec2(1.0f * (float)i, 1.0f * (float)j),
                    glm::vec3(0.0f, 1.0f, 0.0f)
            );
        }
    }
    for(int i = 0; i < 6; ++i) {
        square_indices[i] = { 0,1,2,1,2,3 };
        this->Combine(square_vertices[i], square_indices[i]);
    }

//    this->vertices = {
//            //Pos                 //Tex        //Normal
//            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
//            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  0.0f,  0.0f, -1.0f,
//            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
//            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
//            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f,  0.0f, -1.0f,
//            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
//
//            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f,  0.0f,  1.0f,
//            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f,  0.0f,  1.0f,
//            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
//            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
//            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  0.0f,  0.0f,  1.0f,
//            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f,  0.0f,  1.0f,
//
//            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
//            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
//            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
//            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
//            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
//            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
//
//            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
//            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
//            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
//            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
//            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
//            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
//
//            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
//            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
//            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
//            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
//            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
//            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
//
//            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f,
//            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
//            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
//            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
//            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
//            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f
//    };
//    this->indices =  { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35 };
}
