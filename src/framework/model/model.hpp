//
// Created by syq on 23-7-6.
//
#pragma once

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <stdexcept>
#include <string>
#include "framework/sprites/base.hpp"
#include "framework/texture.hpp"
#include "common/defs.hpp"

class Model {
private:
    std::string directory;
    Texture2D diffuse_map;
    Texture2D specular_map;
    void LoadModel(const std::string& path);
    void ProcessNode(aiNode* node, const aiScene* scene);
    void ProcessMesh(aiMesh* mesh, const aiScene* scene);
    Texture2D ProcessTexture(aiMaterial* material, aiTextureType type);
public:
    Model(const std::string& path);
};


void Model::LoadModel(const std::string& path) {
    Assimp::Importer importer;
    auto scene = importer.ReadFile(path, aiProcess_Triangulate);
    if (!scene || !scene->mRootNode || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) {
        throw std::runtime_error(importer.GetErrorString());
    }
    this->directory = path.substr(0, path.find_last_of('/'));
    this->ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode *node, const aiScene *scene) {
    for(int i = 0; i < node->mNumMeshes; ++i) {
        auto mesh = scene->mMeshes[node->mMeshes[i]];
    }
    for(int i = 0; i < node->mNumChildren; ++i) {
        this->ProcessNode(node->mChildren[i], scene);
    }
}

void Model::ProcessMesh(aiMesh *mesh, const aiScene *scene) {
    GLfloatVec vertices;
    GLuintVec indices;

    for(int i = 0; i < mesh->mNumVertices; ++i) {
        auto position = mesh->mVertices[i];
        auto normal = mesh->mNormals[i];
        auto tex_coord = mesh->mTextureCoords[0] ? mesh->mTextureCoords[0][i] : aiVector3D(0.0f);
        GLfloatVec vertex = { position.x, position.y, position.z, tex_coord.x, tex_coord.y, normal.x, normal.y, normal.z };
        vertices.insert(vertices.end(), vertex.begin(), vertex.end());
    }
    for(int i = 0; i < mesh->mNumFaces; ++i) {
        auto face = mesh->mFaces[i];
        for(int k = 0; k < face.mNumIndices; ++k) {
            indices.push_back(face.mIndices[k]);
        }
    }
    if(mesh->mMaterialIndex >= 0) {
        auto material = scene->mMaterials[mesh->mMaterialIndex];
        this->diffuse_map = this->ProcessTexture(material, aiTextureType_DIFFUSE);
        this->specular_map = this->ProcessTexture(material, aiTextureType_SPECULAR);
    }
}

Texture2D Model::ProcessTexture(aiMaterial* material, aiTextureType type) {
    for(int i = 0; i < material->GetTextureCount(type); ++i) {
        aiString str;
        material->GetTexture(type, i, &str);
        Texture2D texture(directory + "/" + str.C_Str());
        return texture;
    }
}
