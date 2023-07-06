//
// Created by syq on 23-7-5.
//
#pragma once
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <stdexcept>
#include "framework/sprites/base.hpp"
#include "common/defs.hpp"

class Mesh: public BaseSprite {
private:
    Mesh(shared_ptr<Shader>& shader, const std::string& path);
    void LoadModel(const std::string& path);
    void ProcessNode(aiNode* node, const aiScene* scene);
    void ProcessMesh(aiMesh* mesh, const aiScene* scene);
};

Mesh::Mesh(shared_ptr<Shader>& shader, const std::string& path): BaseSprite(shader) {
    this->LoadModel(path);
}

void Mesh::LoadModel(const std::string& path) {
    Assimp::Importer importer;
    auto scene = importer.ReadFile(path, aiProcess_Triangulate);
    if (!scene || !scene->mRootNode || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) {
        throw std::runtime_error(importer.GetErrorString());
    }
    this->ProcessNode(scene->mRootNode, scene);
}

void Mesh::ProcessNode(aiNode *node, const aiScene *scene) {
    for(int i = 0; i < node->mNumMeshes; ++i) {
        auto mesh = scene->mMeshes[node->mMeshes[i]];
    }
    for(int i = 0; i < node->mNumChildren; ++i) {
        this->ProcessNode(node->mChildren[i], scene);
    }
}

void Mesh::ProcessMesh(aiMesh *mesh, const aiScene *scene) {

}
