//
// Created by syq on 23-7-10.
//
#pragma once
#include "common/defs.hpp"
#include "framework/sprites/sphere.hpp"
#include "framework/sprites/base.hpp"
#include "framework/model/model.hpp"

namespace GraphScene {
    vector<shared_ptr<GameObject>> objects;
    shared_ptr<GameObject> skybox;

    void LoadScene();
    void RenderSkybox(shared_ptr<Shader>& shader);
    void RenderObjects(shared_ptr<Shader>& shader);
}

void GraphScene::LoadScene() {
    skybox = std::make_shared<GameObject>(std::make_shared<Cube>("skybox"), glm::vec3(0.0f));
    auto cube = std::make_shared<GameObject>(
            std::make_shared<Cube>("container", "container_spec"),
            glm::vec3(3.0f, 1.0f, 3.0f)
            );

    auto floor = std::make_shared<GameObject>(
            std::make_shared<Floor>("floor", "floor"),
            glm::vec3(0.0f)
            );
    auto nanosuit = std::make_shared<GameObject>(
            std::make_shared<Model>(fs::current_path().parent_path() / "assets" / "meshes" / "nanosuit" / "nanosuit.obj"),
            glm::vec3(0.0f, 0.0f, 3.0f),
            glm::vec3(0.2f)
            );
    auto klee = std::make_shared<GameObject>(
            std::make_shared<Model>(fs::current_path().parent_path() / "assets" / "meshes" / "Klee" / "Klee.pmx"),
            glm::vec3(3.0f, 0.0f, 0.0f),
            glm::vec3(0.2f)
            );
    for(auto & pos : ResourceManager::light_pos) {
        auto sphere = std::make_shared<GameObject>(
                std::make_shared<Sphere>("container", "container_spec"),
                pos,
                glm::vec3(0.3f)
        );
        objects.push_back(sphere);
    }
    objects.push_back(cube);
    objects.push_back(floor);
    objects.push_back(nanosuit);
    objects.push_back(klee);
}

void GraphScene::RenderSkybox(shared_ptr<Shader>& shader) {
    glDepthFunc(GL_LEQUAL);
    skybox->Draw(shader);
    glDepthFunc(GL_LESS);
}

void GraphScene::RenderObjects(shared_ptr<Shader>& shader) {
    for(auto & object : objects) {
        object->Draw(shader);
    }
}
