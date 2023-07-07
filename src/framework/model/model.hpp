//
// Created by syq on 23-7-6.
//
#pragma once

#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <stdexcept>
#include <string>
#include <regex>
#include "framework/sprites/base.hpp"
#include "framework/texture.hpp"
#include "framework/model/mesh.hpp"
#include "scene/resources.hpp"
#include "common/defs.hpp"

class Model {
private:
    std::string directory;
    vector<Mesh> meshes;
    void ProcessNode(aiNode* node, const aiScene* scene);
    void ProcessMesh(aiMesh* mesh, const aiScene* scene);
    std::string ProcessTexture(aiMaterial* material, aiTextureType type);
public:
    explicit Model(const std::string &path);
    ~Model() = default;
    void Draw(
        shared_ptr<Shader>& shader,
        glm::vec3 position,
        glm::vec3 size = glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3 rotate = glm::vec3(0.0f, 0.0f, 0.0f)
    );
};

Model::Model(const std::string &path) {
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
        this->ProcessMesh(mesh, scene);
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
    std::string diffuse_map = "empty";
    std::string specular_map = "empty";
    if(mesh->mMaterialIndex >= 0) {
        auto material = scene->mMaterials[mesh->mMaterialIndex];
        diffuse_map = this->ProcessTexture(material, aiTextureType_DIFFUSE);
        specular_map = this->ProcessTexture(material, aiTextureType_SPECULAR);
    }
    this->meshes.emplace_back(vertices, indices, diffuse_map, specular_map);
}

std::string Model::ProcessTexture(aiMaterial* material, aiTextureType type) {
    for(int i = 0; i < material->GetTextureCount(type); ++i) {
        aiString str;
        material->GetTexture(type, i, &str);
        auto name = std::regex_replace(std::string(str.C_Str()), std::regex("\\\\"), "/");   //转义windows路径
        auto path = fs::path(directory + "/" + name);
        ResourceManager::LoadTexture(path);
        return path.stem().string();
    }
    return "empty";
}

void Model::Draw(shared_ptr<Shader>& shader, glm::vec3 position, glm::vec3 size, glm::vec3 rotate) {
    for(auto &mesh : this->meshes) {
        mesh.LoadBuffer();
        mesh.Draw(shader, position, size, rotate);
    }
}
