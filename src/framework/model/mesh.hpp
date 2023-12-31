//
// Created by syq on 23-7-6.
//
#pragma once
#include "framework/sprites/base.hpp"

class Mesh: public BaseSprite {
public:
    Mesh(VertexArr &vertices, IndiceArr &indices, const std::string &diffuse_map = "empty", const std::string &specular_map = "empty");
    void LoadData() override;
};

Mesh::Mesh(VertexArr &vertices, IndiceArr &indices, const std::string &diffuse_map, const std::string &specular_map): BaseSprite(diffuse_map, specular_map) {
    this->vertices = vertices;
    this->indices = indices;
}

void Mesh::LoadData() {}


