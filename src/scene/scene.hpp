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
#include "framework/particle_system/base.hpp"

namespace GraphScene {
    vector<shared_ptr<GameObject<BaseSprite>>> sprites;
    vector<shared_ptr<GameObject<Model>>> models;

    shared_ptr<GameObject<BaseSprite>> skybox;
    shared_ptr<Billboard> board;
    shared_ptr<ParticleSystem<Fireworks>> fireworks;
    shared_ptr<ParticleSystem<Flame>> flame;

    void LoadScene();
    void RenderSkybox(shared_ptr<Shader>& shader);
    void RenderObjects(shared_ptr<Shader>& shader);
    void RenderBillBoard(shared_ptr<Shader>& shader);
    void RenderParticleSystem();
}

void GraphScene::LoadScene() {
    skybox = std::make_shared<GameObject<BaseSprite>>(std::make_shared<Cube>("skybox"), glm::vec3(0.0f));
    board = std::make_shared<Billboard>("brickwall");

    fireworks = std::make_shared<ParticleSystem<Fireworks>>(vector<std::string>{"star_02"});
    flame = std::make_shared<ParticleSystem<Flame>>(vector<std::string>{"flame_start", "flame_spark"});

    auto cube = std::make_shared<GameObject<BaseSprite>>(
            std::make_shared<Cone>("brickwall"),
            glm::vec3(3.0f, 1.0f, 3.0f),
            glm::vec3(1.0f),
            glm::vec3(glm::radians(90.0f))
            );

    auto floor = std::make_shared<GameObject<BaseSprite>>(
            std::make_shared<Floor>("floor", "floor"),
            glm::vec3(0.0f)
            );
    auto nanosuit = std::make_shared<GameObject<Model>>(
            std::make_shared<Model>(fs::current_path().parent_path() / "assets" / "meshes" / "nanosuit" / "nanosuit.obj"),
            glm::vec3(0.0f, 0.0f, 3.0f),
            glm::vec3(0.2f)
            );
    auto klee = std::make_shared<GameObject<Model>>(
            std::make_shared<Model>(fs::current_path().parent_path() / "assets" / "meshes" / "Klee" / "Klee.pmx"),
            glm::vec3(3.0f, 0.0f, 0.0f),
            glm::vec3(0.2f)
            );
    for(auto & light_point : ResourceManager::light_points) {
        auto sphere = std::make_shared<GameObject<BaseSprite>>(
                std::make_shared<Sphere>("container", "container_spec"),
                light_point.position,
                glm::vec3(0.3f)
        );
        sprites.push_back(sphere);
    }
    sprites.push_back(cube);
    sprites.push_back(floor);
    models.push_back(nanosuit);
    models.push_back(klee);
}

void GraphScene::RenderSkybox(shared_ptr<Shader>& shader) {
    glDepthFunc(GL_LEQUAL);
    skybox->Draw(shader);
    glDepthFunc(GL_LESS);
}

void GraphScene::RenderObjects(shared_ptr<Shader>& shader) {
    for(auto & sprite : sprites) {
        sprite->Draw(shader);
    }
    for(auto &model : models) {
        model->Draw(shader);
    }
}

void GraphScene::RenderBillBoard(shared_ptr<Shader>& shader) {
    board->Render(shader);
}

void GraphScene::RenderParticleSystem() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    fireworks->Render(
            ResourceManager::shader_fireworks_update,
            ResourceManager::shader_fireworks_render,
            glm::vec3(15.0f, 0.1f, 15.0f),
            glm::vec3(0.0f)
            );
    flame->Render(
            ResourceManager::shader_flame_update,
            ResourceManager::shader_flame_render,
            SceneStatus::flame_center,
            glm::vec3(0.0f)
            );
    glDisable(GL_BLEND);
}
