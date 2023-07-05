//
// Created by chty on 23-7-4.
//

#pragma once
#include <utility>

#include "framework/sprites/base.hpp"

class Floor: public BaseSprite {
public:
    explicit Floor(shared_ptr<Shader>& shader);
    ~Floor() override = default;
    void LoadData() override;
};

void Floor::LoadData() {
    this->vertices = {
            //Pos                   //Tex        //Normal
            -499.5f, 0.0f,  499.5f, 0.0f,   100.0f, 0.0f, 1.0f, 0.0f,
            499.5f, 0.0f, -499.5f, 100.0f,   0.0f, 0.0f, 1.0f, 0.0f,
            -499.5f, 0.0f, -499.5f, 0.0f,     0.0f, 0.0f, 1.0f, 0.0f,
            499.5f, 0.0f,  499.5f, 100.0f, 100.0f, 0.0f, 1.0f, 0.0f
    };
    this->indices = { 0,1,2,0,1,3 };
}

Floor::Floor(shared_ptr<Shader>& shader) : BaseSprite(shader) {}
