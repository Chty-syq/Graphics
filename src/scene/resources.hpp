//
// Created by syq on 23-7-7.
//
#pragma once
#include <stdexcept>
#include <map>
#include <queue>
#include "framework/texture.hpp"
#include "common/structs.hpp"
#include "common/defs.hpp"


namespace ResourceManager {
    std::map<std::string, shared_ptr<Texture2D>> textures;
    shared_ptr<Shader> shader_object;
    shared_ptr<Shader> shader_skybox;
    shared_ptr<Shader> shader_screen;
    shared_ptr<Shader> shader_depth;

    LightParal light_paral;
    vector<LightPoint> light_points;
    LightSpot light_spot;

    void Init();

    void LoadTexture(const std::string &path);
    void LoadTexture(const std::string &path, const std::string &name);
    void LoadTextures(const std::string &directory);
    void LoadTextureCube(const std::string &directory);
    void BindTexture(const std::string &name, int index);
    shared_ptr<Texture2D> GetTexture(const std::string &name);

    void LoadLights();
    void LoadShaderObject();
};

void ResourceManager::Init() {
    LoadTexture("", "empty");
    LoadTextures(fs::current_path().parent_path() / "assets" / "textures");
    LoadTextureCube(fs::current_path().parent_path() / "assets" / "textures_cube" / "skybox");
    LoadLights();
    LoadShaderObject();
}

void ResourceManager::LoadTexture(const std::string &path) {
    auto name = fs::path(path).stem().string();
    LoadTexture(path, name);
}

void ResourceManager::LoadTexture(const std::string &path, const std::string &name) {
    if (textures.contains(name)) return;
    auto texture = std::make_shared<Texture2D>(vector{path});
    textures.insert(std::make_pair(name, texture));
}

void ResourceManager::LoadTextures(const std::string &directory) {
    std::queue<std::string> directories;
    directories.push(directory);
    while(!directories.empty()) {
        auto node = directories.back();
        directories.pop();
        for(const auto& entry: fs::directory_iterator(node)) {
            if (fs::is_directory(entry)) {
                directories.push(entry.path());
            } else {
                LoadTexture(entry.path());
            }
        }
    }
}

void ResourceManager::LoadTextureCube(const std::string &directory) {
    auto name = fs::path(directory).stem().string();
    vector<std::string> paths = {
            directory + "/right.jpg",
            directory + "/left.jpg",
            directory + "/top.jpg",
            directory + "/bottom.jpg",
            directory + "/front.jpg",
            directory + "/back.jpg",
    };
    auto texture = std::make_shared<Texture2D>(paths, GL_TEXTURE_CUBE_MAP, false);
    textures.insert(std::make_pair(name, texture));
}

shared_ptr<Texture2D> ResourceManager::GetTexture(const std::string &name) {
    return textures[name];
}

void ResourceManager::BindTexture(const std::string &name, int index) {
    if (!textures.contains(name)) {
        throw std::runtime_error("Texture not Exist!");
    }
    auto texture = textures[name];
    texture->Bind(index);
}

void ResourceManager::LoadLights() {
    light_paral = {
        glm::vec3(-0.2f, -1.0f, -0.3f),{
            glm::vec3(0.05f, 0.05f, 0.05f),
            glm::vec3(0.4f, 0.4f, 0.4f),
            glm::vec3(0.5f, 0.5f, 0.5f)
        }
    };
    LightFactor factor = {
        glm::vec3(0.05f, 0.05f, 0.05f),
        glm::vec3(0.8f, 0.8f, 0.8f),
        glm::vec3(1.0f, 1.0f, 1.0f)
    };
    auto coefficient = glm::vec3(1.0f, 0.09f, 0.032f);
    light_points.push_back({glm::vec3(0.7f,  4.2f,  2.0f), coefficient, factor});
    light_points.push_back({glm::vec3(2.3f, 3.3f, -4.0f), coefficient, factor});
    light_points.push_back({glm::vec3(-4.0f,  2.0f, -12.0f), coefficient, factor});
    light_points.push_back({glm::vec3(0.0f,  1.0f, -3.0f), coefficient, factor});
    light_spot = {
        glm::cos(glm::radians(12.5f)),
        glm::cos(glm::radians(17.5f)),{
            glm::vec3(0.0f),
            coefficient,{
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(1.0f, 1.0f, 1.0f),
                glm::vec3(1.0f, 1.0f, 1.0f)
                }}
    };
}

void ResourceManager::LoadShaderObject() {
    auto projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 7.5f);
    auto view = glm::lookAt(light_paral.direction * (-4.0f), glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    shader_object = std::make_shared<Shader>(fs::current_path().parent_path() / "shaders" / "normal");
    shader_object->Use();
    shader_object->SetAttribute("mLightSpace", projection * view);
    shader_object->SetAttribute("fShadowMap", 2);
    shader_object->SetAttribute("material.mDiffuse", 0);
    shader_object->SetAttribute("material.mSpecular", 1);
    shader_object->SetAttribute("material.mShininess", 0.4f * 128);
    shader_object->SetLightParal(light_paral);
    shader_object->SetLightPoint(light_points[0], 0);
    shader_object->SetLightPoint(light_points[1], 1);
    shader_object->SetLightPoint(light_points[2], 2);
    shader_object->SetLightPoint(light_points[3], 3);
    shader_object->SetLightSpot(light_spot);

    shader_skybox = std::make_shared<Shader>(fs::current_path().parent_path() / "shaders" / "skybox");
    shader_skybox->Use();
    shader_skybox->SetAttribute("fSkybox", 0);

    shader_screen = std::make_shared<Shader>(fs::current_path().parent_path() / "shaders" / "screen");
    shader_screen->Use();
    shader_screen->SetAttribute("fScreen", 0);

    shader_depth = std::make_shared<Shader>(fs::current_path().parent_path() / "shaders" / "depth");
    shader_depth->Use();
    shader_depth->SetAttribute("mLightSpace", projection * view);
}
