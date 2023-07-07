//
// Created by syq on 23-7-7.
//
#pragma once
#include <stdexcept>
#include <map>
#include "framework/texture.hpp"
#include "common/defs.hpp"


namespace ResourceManager {
    std::map<std::string, shared_ptr<Texture2D>> textures;
    shared_ptr<Shader> shader_obj;

    void Init();

    void LoadTexture(const std::string &path);
    void LoadTexture(const std::string &path, const std::string &name);
    void LoadTextures(const std::string &directory);
    void BindTexture(const std::string &name, int index);
    shared_ptr<Texture2D> GetTexture(const std::string &name);

    void LoadShaderObject();
};

void ResourceManager::Init() {
    LoadTexture("", "empty");
    LoadTextures(fs::current_path().parent_path() / "assets" / "textures");
    LoadShaderObject();
}

void ResourceManager::LoadTexture(const std::string &path) {
    auto name = fs::path(path).stem().string();
    LoadTexture(path, name);
}

void ResourceManager::LoadTexture(const std::string &path, const std::string &name) {
    if (textures.contains(name)) {
        std::cerr << "[Warning] Duplicated Texture of " + name << std::endl;
        return;
    }
    auto texture = std::make_shared<Texture2D>(path);
    textures.insert(std::make_pair(name, texture));
}

void ResourceManager::LoadTextures(const std::string &directory) {
    for(const auto& entry: fs::directory_iterator(directory)) {
        if (fs::is_directory(entry)) {
            LoadTextures(entry.path());
        } else {
            LoadTexture(entry.path());
        }
    }
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
    shader_obj = std::make_shared<Shader>(fs::current_path().parent_path() / "shaders" / "normal");
    shader_obj->Use();
    shader_obj->SetAttribute("material.mDiffuse", 0);
    shader_obj->SetAttribute("material.mSpecular", 1);
    shader_obj->SetAttribute("material.mShininess", 0.4f * 128);
    shader_obj->SetAttribute("fLightParal.pDirection", glm::vec3(-0.2f, -1.0f, -0.3f));
    shader_obj->SetAttribute("fLightParal.pFactor.fAmbient", glm::vec3(0.05f, 0.05f, 0.05f));
    shader_obj->SetAttribute("fLightParal.pFactor.fDiffuse", glm::vec3(0.4f, 0.4f, 0.4f));
    shader_obj->SetAttribute("fLightParal.pFactor.fSpecular", glm::vec3(0.5f, 0.5f, 0.5f));
    shader_obj->SetAttribute("fLightPoint[0].pPosition", glm::vec3(0.7f,  0.2f,  2.0f));
    shader_obj->SetAttribute("fLightPoint[0].pCoefficient", glm::vec3(1.0f, 0.09f, 0.032f));
    shader_obj->SetAttribute("fLightPoint[0].pFactor.fAmbient", glm::vec3(0.05f, 0.05f, 0.05f));
    shader_obj->SetAttribute("fLightPoint[0].pFactor.fDiffuse", glm::vec3(0.8f, 0.8f, 0.8f));
    shader_obj->SetAttribute("fLightPoint[0].pFactor.fSpecular", glm::vec3(1.0f, 1.0f, 1.0f));
    shader_obj->SetAttribute("fLightPoint[1].pPosition", glm::vec3(2.3f, -3.3f, -4.0f));
    shader_obj->SetAttribute("fLightPoint[1].pCoefficient", glm::vec3(1.0f, 0.09f, 0.032f));
    shader_obj->SetAttribute("fLightPoint[1].pFactor.fAmbient", glm::vec3(0.05f, 0.05f, 0.05f));
    shader_obj->SetAttribute("fLightPoint[1].pFactor.fDiffuse", glm::vec3(0.8f, 0.8f, 0.8f));
    shader_obj->SetAttribute("fLightPoint[1].pFactor.fSpecular", glm::vec3(1.0f, 1.0f, 1.0f));
    shader_obj->SetAttribute("fLightPoint[2].pPosition", glm::vec3(-4.0f,  2.0f, -12.0f));
    shader_obj->SetAttribute("fLightPoint[2].pCoefficient", glm::vec3(1.0f, 0.09f, 0.032f));
    shader_obj->SetAttribute("fLightPoint[2].pFactor.fAmbient", glm::vec3(0.05f, 0.05f, 0.05f));
    shader_obj->SetAttribute("fLightPoint[2].pFactor.fDiffuse", glm::vec3(0.8f, 0.8f, 0.8f));
    shader_obj->SetAttribute("fLightPoint[2].pFactor.fSpecular", glm::vec3(1.0f, 1.0f, 1.0f));
    shader_obj->SetAttribute("fLightPoint[3].pPosition", glm::vec3(0.0f,  0.0f, -3.0f));
    shader_obj->SetAttribute("fLightPoint[3].pCoefficient", glm::vec3(1.0f, 0.09f, 0.032f));
    shader_obj->SetAttribute("fLightPoint[3].pFactor.fAmbient", glm::vec3(0.05f, 0.05f, 0.05f));
    shader_obj->SetAttribute("fLightPoint[3].pFactor.fDiffuse", glm::vec3(0.8f, 0.8f, 0.8f));
    shader_obj->SetAttribute("fLightPoint[3].pFactor.fSpecular", glm::vec3(1.0f, 1.0f, 1.0f));
    shader_obj->SetAttribute("fLightSpot.sCutoffInner", glm::cos(glm::radians(12.5f)));
    shader_obj->SetAttribute("fLightSpot.sCutoffOuter", glm::cos(glm::radians(17.5f)));
    shader_obj->SetAttribute("fLightSpot.sLightPoint.pCoefficient", glm::vec3(1.0f, 0.09f, 0.032f));
    shader_obj->SetAttribute("fLightSpot.sLightPoint.pFactor.fAmbient", glm::vec3(0.0f, 0.0f, 0.0f));
    shader_obj->SetAttribute("fLightSpot.sLightPoint.pFactor.fDiffuse", glm::vec3(1.0f, 1.0f, 1.0f));
    shader_obj->SetAttribute("fLightSpot.sLightPoint.pFactor.fSpecular", glm::vec3(1.0f, 1.0f, 1.0f));
}