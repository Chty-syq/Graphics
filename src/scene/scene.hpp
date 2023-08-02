//
// Created by syq on 23-7-10.
//
#pragma once
#include "common/defs.hpp"
#include "framework/sprites/2D/floor.hpp"
#include "framework/sprites/2D/cycle.hpp"
#include "framework/sprites/3D/sphere.hpp"
#include "framework/sprites/3D/cylinder.hpp"
#include "framework/sprites/3D/cone.hpp"
#include "framework/sprites/3D/cube.hpp"
#include "framework/sprites/base.hpp"
#include "framework/model/model.hpp"

namespace GraphScene {
    vector<shared_ptr<GameObject>> objects;
    shared_ptr<GameObject> skybox;
    shared_ptr<Billboard> board;
    shared_ptr<ParticleSystem> fireworks;

    void LoadScene();
    void RenderSkybox(shared_ptr<Shader>& shader);
    void RenderObjects(shared_ptr<Shader>& shader);
    void RenderBillBoard(shared_ptr<Shader>& shader);
    void RenderParticleSystem(shared_ptr<Shader>& shader_update, shared_ptr<Shader>& shader_render);
}

void GraphScene::LoadScene() {
    skybox = std::make_shared<GameObject>(std::make_shared<Cube>("skybox"), glm::vec3(0.0f));
    board = std::make_shared<Billboard>("brickwall");
    fireworks = std::make_shared<ParticleSystem>(glm::vec3(15.0f, 0.1f, 15.0f), "star_02");

    auto cube = std::make_shared<GameObject>(
            std::make_shared<Cone>("brickwall"),
            glm::vec3(3.0f, 1.0f, 3.0f),
            glm::vec3(1.0f),
            glm::vec3(glm::radians(90.0f))
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
    for(auto & light_point : ResourceManager::light_points) {
        auto sphere = std::make_shared<GameObject>(
                std::make_shared<Sphere>("container", "container_spec"),
                light_point.position,
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

void GraphScene::RenderBillBoard(shared_ptr<Shader>& shader) {
    board->Render(shader);
}

void GraphScene::RenderParticleSystem(shared_ptr<Shader>& shader_update, shared_ptr<Shader>& shader_render) {
    fireworks->Render(shader_update, shader_render);
}
