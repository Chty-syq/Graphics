//
// Created by syq on 23-8-17.
//

#pragma once
#include "common/transformation.hpp"

class FractalTree {
private:
    std::string texture;
    int level;

    struct Status {
        glm::vec3 position;
        glm::vec3 direction;
        float length;
        float radius;
        int level;
    };

    std::string generation;
    Status status{};
    vector<GameObject<Cylinder>> trunks;

    const float delta_x = 35.0f;
    const float delta_y = 30.0f;
    const float delta_z = 35.0f;
    const float length_factor = 0.75f;
    const float radius_factor = 0.72f;

public:
    FractalTree(const std::string& texture, int level);
    void Generate();
    void Render(shared_ptr<Shader>& shader);
};

FractalTree::FractalTree(const std::string& texture, int level) {
    Grammar::Clear();
    Grammar::AddGeneration('S', "F[^$X][*%X][&%X]");
    Grammar::AddGeneration('X', "F[^%D][&$D][/$D][*%D]");
    Grammar::AddGeneration('X', "F[&%D][*$D][/$D][^%D]");
    Grammar::AddGeneration('D', "F[^$X][*%FX][&%X]");

    generation = Grammar::Iteration("S", level);

    this->texture = texture;
    this->level = level;
    this->Generate();
}

void FractalTree::Generate() {
    status = {
            .position = glm::vec3(0.0f),
            .direction = glm::vec3(0.0f, 1.0f, 0.0f),
            .length = 1.0f,
            .radius = 0.05f,
            .level = 1
    };

    std::stack<Status> status_stack;
    for(const auto& target : generation) {
        switch (target) {
            case 'F': {
                glm::vec3 axis = glm::cross(status.direction, glm::vec3(0.0f, 1.0f, 0.0f));
                trunks.emplace_back(
                        std::make_shared<Cylinder>(texture),
                        status.position,
                        transformation::RotateVec(glm::vec3(0.0f, 1.0f, 0.0f), status.direction),
                        glm::vec3(status.radius, status.length, status.radius)
                        );
                status.position += status.direction * status.length;
                break;
            }
            case '$': status.direction = transformation::RotateY(status.direction, glm::radians(delta_y)); break;
            case '%': status.direction = transformation::RotateY(status.direction, glm::radians(-delta_y)); break;
            case '^': status.direction = transformation::RotateX(status.direction, glm::radians(delta_x)); break;
            case '&': status.direction = transformation::RotateX(status.direction, glm::radians(-delta_x)); break;
            case '*': status.direction = transformation::RotateZ(status.direction, glm::radians(delta_z)); break;
            case '/': status.direction = transformation::RotateZ(status.direction, glm::radians(-delta_z)); break;
            case '[': {
                status_stack.push(status);
                status.length *= length_factor;
                status.radius *= radius_factor;
                status.level += 1;
                break;
            }
            case ']': {
                status = status_stack.top();
                status_stack.pop();
                break;
            }
            default: break;
        }
    }
}

void FractalTree::Render(shared_ptr<Shader>& shader) {
    for(auto & trunk : trunks) {
        trunk.Draw(shader);
    }
}

