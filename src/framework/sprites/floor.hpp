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
    this->vertices = {
            //Pos                   //Tex        //Normal
            -25.0f, 0.0f,  25.0f, 0.0f,   25.0f, 0.0f, 1.0f, 0.0f,
            25.0f, 0.0f, -25.0f, 25.0f,   0.0f, 0.0f, 1.0f, 0.0f,
            -25.0f, 0.0f, -25.0f, 0.0f,     0.0f, 0.0f, 1.0f, 0.0f,
            25.0f, 0.0f,  25.0f, 25.0f, 25.0f, 0.0f, 1.0f, 0.0f
    };
    this->indices = { 0,1,2,0,1,3 };
}
