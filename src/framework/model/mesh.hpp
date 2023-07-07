//
// Created by syq on 23-7-6.
//
#pragma once
#include "framework/sprites/base.hpp"

class Mesh: public BaseSprite {
public:
    Mesh(GLfloatVec &vertices, GLuintVec &indices);
    Mesh(GLfloatVec &vertices, GLuintVec &indices, const std::string &diffuse_map, const std::string &specular_map);
    ~Mesh() override = default;
    void LoadData() override;
};

Mesh::Mesh(GLfloatVec &vertices, GLuintVec &indices) {
    this->vertices = vertices;
    this->indices = indices;
}

Mesh::Mesh(GLfloatVec &vertices, GLuintVec &indices, const std::string &diffuse_map, const std::string &specular_map): BaseSprite(diffuse_map, specular_map) {
    this->vertices = vertices;
    this->indices = indices;
}

void Mesh::LoadData() {}


