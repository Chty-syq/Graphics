//
// Created by syq on 23-8-23.
//

#pragma once
#include "framework/ray_tracing/ray.hpp"

struct Material;

struct HitRecord {
    float t;
    glm::vec3 position;
    glm::vec3 normal;
    shared_ptr<Material> material;
};

class Hittable {
public:
    Hittable() = default;
    virtual ~Hittable() {}
    virtual bool Hit(const Ray &ray, float t_min, float t_max, HitRecord &result) const = 0;
};