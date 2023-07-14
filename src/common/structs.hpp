//
// Created by syq on 23-7-13.
//

#pragma once

#include "glm/vec3.hpp"

struct LightFactor {
    glm::vec3   ambient;
    glm::vec3   diffuse;
    glm::vec3   specular;
};

struct LightParal {
    glm::vec3   direction;
    LightFactor factor;
};

struct LightPoint {
    glm::vec3   position;
    glm::vec3   coefficient;
    LightFactor factor;
};

struct LightSpot {
    float       cutoff_inner;
    float       cutoff_outer;
    LightPoint  light_point;
};
