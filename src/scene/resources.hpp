//
// Created by syq on 23-7-7.
//
#pragma once
#include <stdexcept>
#include <map>
#include <queue>
#include "framework/texture.hpp"
#include "common/defs.hpp"


namespace ResourceManager {
    std::map<std::string, shared_ptr<Texture2D>> textures;
    shared_ptr<Shader> shader_object;
    shared_ptr<Shader> shader_skybox;
    shared_ptr<Shader> shader_screen;

    vector<glm::vec3> light_pos = {
            glm::vec3(0.7f,  0.2f,  2.0f),
            glm::vec3(2.3f, 3.3f, -4.0f),
            glm::vec3(-4.0f,  2.0f, -12.0f),
            glm::vec3(0.0f,  1.0f, -3.0f)
    };

    void Init();

    void LoadTexture(const std::string &path);
    void LoadTexture(const std::string &path, const std::string &name);
    void LoadTextures(const std::string &directory);
    void LoadTextureCube(const std::string &directory);
    void BindTexture(const std::string &name, int index);
    shared_ptr<Texture2D> GetTexture(const std::string &name);

    void LoadShaderObject();
};

void ResourceManager::Init() {
    LoadTexture("", "empty");
    LoadTextures(fs::current_path().parent_path() / "assets" / "textures");
    LoadTextureCube(fs::current_path().parent_path() / "assets" / "textures_cube" / "skybox");
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

void ResourceManager::LoadShaderObject() {
    shader_object = std::make_shared<Shader>(fs::current_path().parent_path() / "shaders" / "normal");
    shader_object->Use();
    shader_object->SetAttribute("material.mDiffuse", 0);
    shader_object->SetAttribute("material.mSpecular", 1);
    shader_object->SetAttribute("material.mShininess", 0.4f * 128);
    shader_object->SetAttribute("fLightParal.pDirection", glm::vec3(-0.2f, -1.0f, -0.3f));
    shader_object->SetAttribute("fLightParal.pFactor.fAmbient", glm::vec3(0.05f, 0.05f, 0.05f));
    shader_object->SetAttribute("fLightParal.pFactor.fDiffuse", glm::vec3(0.4f, 0.4f, 0.4f));
    shader_object->SetAttribute("fLightParal.pFactor.fSpecular", glm::vec3(0.5f, 0.5f, 0.5f));
    shader_object->SetAttribute("fLightPoint[0].pPosition", ResourceManager::light_pos[0]);
    shader_object->SetAttribute("fLightPoint[0].pCoefficient", glm::vec3(1.0f, 0.09f, 0.032f));
    shader_object->SetAttribute("fLightPoint[0].pFactor.fAmbient", glm::vec3(0.05f, 0.05f, 0.05f));
    shader_object->SetAttribute("fLightPoint[0].pFactor.fDiffuse", glm::vec3(0.8f, 0.8f, 0.8f));
    shader_object->SetAttribute("fLightPoint[0].pFactor.fSpecular", glm::vec3(1.0f, 1.0f, 1.0f));
    shader_object->SetAttribute("fLightPoint[1].pPosition", ResourceManager::light_pos[1]);
    shader_object->SetAttribute("fLightPoint[1].pCoefficient", glm::vec3(1.0f, 0.09f, 0.032f));
    shader_object->SetAttribute("fLightPoint[1].pFactor.fAmbient", glm::vec3(0.05f, 0.05f, 0.05f));
    shader_object->SetAttribute("fLightPoint[1].pFactor.fDiffuse", glm::vec3(0.8f, 0.8f, 0.8f));
    shader_object->SetAttribute("fLightPoint[1].pFactor.fSpecular", glm::vec3(1.0f, 1.0f, 1.0f));
    shader_object->SetAttribute("fLightPoint[2].pPosition", ResourceManager::light_pos[2]);
    shader_object->SetAttribute("fLightPoint[2].pCoefficient", glm::vec3(1.0f, 0.09f, 0.032f));
    shader_object->SetAttribute("fLightPoint[2].pFactor.fAmbient", glm::vec3(0.05f, 0.05f, 0.05f));
    shader_object->SetAttribute("fLightPoint[2].pFactor.fDiffuse", glm::vec3(0.8f, 0.8f, 0.8f));
    shader_object->SetAttribute("fLightPoint[2].pFactor.fSpecular", glm::vec3(1.0f, 1.0f, 1.0f));
    shader_object->SetAttribute("fLightPoint[3].pPosition", ResourceManager::light_pos[3]);
    shader_object->SetAttribute("fLightPoint[3].pCoefficient", glm::vec3(1.0f, 0.09f, 0.032f));
    shader_object->SetAttribute("fLightPoint[3].pFactor.fAmbient", glm::vec3(0.05f, 0.05f, 0.05f));
    shader_object->SetAttribute("fLightPoint[3].pFactor.fDiffuse", glm::vec3(0.8f, 0.8f, 0.8f));
    shader_object->SetAttribute("fLightPoint[3].pFactor.fSpecular", glm::vec3(1.0f, 1.0f, 1.0f));
    shader_object->SetAttribute("fLightSpot.sCutoffInner", glm::cos(glm::radians(12.5f)));
    shader_object->SetAttribute("fLightSpot.sCutoffOuter", glm::cos(glm::radians(17.5f)));
    shader_object->SetAttribute("fLightSpot.sLightPoint.pCoefficient", glm::vec3(1.0f, 0.09f, 0.032f));
    shader_object->SetAttribute("fLightSpot.sLightPoint.pFactor.fAmbient", glm::vec3(0.0f, 0.0f, 0.0f));
    shader_object->SetAttribute("fLightSpot.sLightPoint.pFactor.fDiffuse", glm::vec3(1.0f, 1.0f, 1.0f));
    shader_object->SetAttribute("fLightSpot.sLightPoint.pFactor.fSpecular", glm::vec3(1.0f, 1.0f, 1.0f));

    shader_skybox = std::make_shared<Shader>(fs::current_path().parent_path() / "shaders" / "skybox");
    shader_skybox->Use();
    shader_skybox->SetAttribute("fSkybox", 0);

    shader_screen = std::make_shared<Shader>(fs::current_path().parent_path() / "shaders" / "screen");
    shader_screen->Use();
    shader_screen->SetAttribute("fScreen", 0);
}
