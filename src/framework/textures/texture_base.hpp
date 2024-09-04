//
// Created by syq on 24-9-3.
//

#pragma once

#include <GLFW/glfw3.h>
#include <cstdio>
#include <string>
#include <utility>
#include <stdexcept>

class TextureBase {
protected:
    GLuint id{};
    GLuint type{};

public:
    ~TextureBase();

    void Bind(int index) const;
};

TextureBase::~TextureBase() {
    glDeleteTextures(1, &this->id);
}

void TextureBase::Bind(int index) const {
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(this->type, this->id);
}
