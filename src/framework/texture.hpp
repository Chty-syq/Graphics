//
// Created by chty on 23-6-29.
//
#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include <GLFW/glfw3.h>
#include <cstdio>
#include <string>
#include <utility>
#include <stdexcept>
#include "stb_image.h"

class Texture2D {
private:
    std::string path;
    GLuint id{};

public:
    explicit Texture2D(const std::string& path);
    ~Texture2D();
    void Use() const;
};

Texture2D::Texture2D(const std::string& path): path(path) {
    glGenTextures(1, &this->id);
    glBindTexture(GL_TEXTURE_2D, this->id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, channels;
    auto bytes = stbi_load(path.c_str(), &width, &height, &channels, 0);
    if (bytes == nullptr) {
        throw std::runtime_error("Load image failed!");
    }

    GLenum format;
    switch (channels) {
        case 1: format = GL_RED; break;
        case 3: format = GL_RGB; break;
        case 4: format = GL_RGBA; break;
        default: throw std::runtime_error("Unexpected channels!");
    }
    glTexImage2D(GL_TEXTURE_2D, 0, (int)format, width, height, 0, format, GL_UNSIGNED_BYTE, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(bytes);
}

Texture2D::~Texture2D() {
    glDeleteTextures(1, &this->id);
}

void Texture2D::Use() const {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->id);
}


