//
// Created by syq on 23-7-31.
//

#pragma once
#include "common/utils.hpp"

class TextureRandom {
private:
    GLuint id{};
public:
    explicit TextureRandom(int size);
    ~TextureRandom();
    void Bind(int index) const;
};

TextureRandom::TextureRandom(int size) {
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_1D, id);

    glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);

    vector<glm::vec3> bytes;
    for(int i = 0; i < size; ++i) {
        float r = utils::RandomFloat(0.0f, 1.0f);
        float g = utils::RandomFloat(0.0f, 1.0f);
        float b = utils::RandomFloat(0.0f, 1.0f);
        bytes.emplace_back(r, g, b);
    }
    glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, size, 0, GL_RGB, GL_FLOAT, bytes.data());
}

TextureRandom::~TextureRandom() {
    glDeleteTextures(1, &this->id);
}

void TextureRandom::Bind(int index) const {
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_1D, this->id);
}
