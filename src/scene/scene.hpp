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
#include "framework/fractal_system/grammar.hpp"
#include "framework/fractal_system/fractal_tree.hpp"

namespace GraphScene {
    vector<shared_ptr<GameObject<BaseSprite>>> sprites;
    vector<shared_ptr<GameObject<Model>>> models;

    shared_ptr<GameObject<BaseSprite>> skybox;
    shared_ptr<Billboard> board;
    shared_ptr<GameObject<ParticleSystem<Fireworks>>> fireworks;
    shared_ptr<GameObject<ParticleSystem<Flame>>> flame;
    shared_ptr<GameObject<ParticleSystem<Fountain>>> fountain;
    shared_ptr<GameObject<FractalTree>> tree;

    void LoadScene();
    void RenderSkybox(shared_ptr<Shader>& shader);
    void RenderObjects(shared_ptr<Shader>& shader);
    void RenderBillBoard(shared_ptr<Shader>& shader);
    void RenderParticleSystem();
}

void GraphScene::LoadScene() {
    skybox = std::make_shared<GameObject<BaseSprite>>(std::make_shared<Cube>("skybox"), glm::vec3(0.0f));
    board = std::make_shared<Billboard>("brickwall");

    fireworks = std::make_shared<GameObject<ParticleSystem<Fireworks>>>(
            std::make_shared<ParticleSystem<Fireworks>>(vector<std::string>{"star_02"}),
            glm::vec3(15.0f, 0.1f, 15.0f),
            glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
            glm::vec3(1.0f)
            );
    flame = std::make_shared<GameObject<ParticleSystem<Flame>>>(
            std::make_shared<ParticleSystem<Flame>>(vector<std::string>{"flame_start", "flame_spark"}),
            glm::vec3(0.0f),
            glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
            glm::vec3(1.0f)
            );
    fountain = std::make_shared<GameObject<ParticleSystem<Fountain>>>(
            std::make_shared<ParticleSystem<Fountain>>(vector<std::string>{"circle_05"}),
            glm::vec3(-3.0f, 0.0f, -10.0f),
            glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
            glm::vec3(0.3f)
            );
    tree = std::make_shared<GameObject<FractalTree>>(
            std::make_shared<FractalTree>("brickwall", 5),
            glm::vec3(3.0f, 0.0f, -3.0f)
            );

    auto cube = std::make_shared<GameObject<BaseSprite>>(
            std::make_shared<Cone>("brickwall"),
            glm::vec3(3.0f, 1.0f, 3.0f),
            glm::angleAxis(glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
            glm::vec3(1.0f)
            );

    auto floor = std::make_shared<GameObject<BaseSprite>>(
            std::make_shared<Floor>("floor", "floor"),
            glm::vec3(0.0f)
            );
    auto nanosuit = std::make_shared<GameObject<Model>>(
            std::make_shared<Model>(fs::current_path().parent_path() / "assets" / "meshes" / "nanosuit" / "nanosuit.obj"),
            glm::vec3(0.0f, 0.0f, 3.0f),
            glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
            glm::vec3(0.2f)
            );
    auto klee = std::make_shared<GameObject<Model>>(
            std::make_shared<Model>(fs::current_path().parent_path() / "assets" / "meshes" / "Klee" / "Klee.pmx"),
            glm::vec3(3.0f, 0.0f, 0.0f),
            glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
            glm::vec3(0.2f)
            );
    for(auto & light_point : ResourceManager::light_points) {
        auto sphere = std::make_shared<GameObject<BaseSprite>>(
                std::make_shared<Sphere>("container", "container_spec"),
                light_point.position,
                glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
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
    skybox->Render(shader);
    glDepthFunc(GL_LESS);
}

void GraphScene::RenderObjects(shared_ptr<Shader>& shader) {
    for(auto & sprite : sprites) {
        sprite->Render(shader);
    }
    for(auto &model : models) {
        model->Render(shader);
    }
    tree->Render(shader);
}

void GraphScene::RenderBillBoard(shared_ptr<Shader>& shader) {
    board->Render(shader);
}

void GraphScene::RenderParticleSystem() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    fireworks->Render(ResourceManager::shader_fireworks_update, ResourceManager::shader_fireworks_render);
    flame->Render(ResourceManager::shader_flame_update, ResourceManager::shader_flame_render);
    fountain->Render(ResourceManager::shader_fountain_update, ResourceManager::shader_fountain_render);
    glDisable(GL_BLEND);
}
