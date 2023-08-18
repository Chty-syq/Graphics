//
// Created by syq on 23-8-18.
//

#pragma once

#include "common/defs.hpp"

namespace transformation {
    glm::vec3 RotateX(glm::vec3 vec, float angle) {
        glm::mat4 mat(1.0f);
        mat = glm::rotate(mat, angle, glm::vec3(1.0f, 0.0f, 0.0f));
        vec = glm::vec3(mat * glm::vec4(vec, 1.0f));
        return vec;
    }

    glm::vec3 RotateY(glm::vec3 vec, float angle) {
        glm::mat4 mat(1.0f);
        mat = glm::rotate(mat, angle, glm::vec3(0.0f, 1.0f, 0.0f));
        vec = glm::vec3(mat * glm::vec4(vec, 1.0f));
        return vec;
    }

    glm::vec3 RotateZ(glm::vec3 vec, float angle) {
        glm::mat4 mat(1.0f);
        mat = glm::rotate(mat, angle, glm::vec3(0.0f, 0.0f, 1.0f));
        vec = glm::vec3(mat * glm::vec4(vec, 1.0f));
        return vec;
    }

    glm::quat RotateVec(glm::vec3 src, glm::vec3 dest) {
        src = glm::normalize(src);
        dest = glm::normalize(dest);

        auto cos_theta = glm::dot(src, dest);
        auto axis = glm::cross(src, dest);

        float s = sqrt((1 + cos_theta) * 2);

        return {s * 0.5f, axis.x / s, axis.y / s, axis.z / s};
    }
}