//
// Created by syq on 24-9-3.
//

#pragma once

#include "framework/textures/texture_base.hpp"

class Texture2D : public TextureBase {
private:
    std::string path;

public:
    explicit Texture2D(const std::string &path, bool flip = true);
};

Texture2D::Texture2D(const std::string &path, bool flip) : path(path) {
    this->type = GL_TEXTURE_2D;

    glGenTextures(1, &this->id);
    glBindTexture(type, this->id);

    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_set_flip_vertically_on_load(flip);

    int width, height, channels;
    auto bytes = stbi_load(path.c_str(), &width, &height, &channels, 0);
    if (bytes == nullptr) {
        cout << width << " " << height << " " << channels << endl;
        std::vector<GLubyte> empty_data(width * height * 4, 0);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, &empty_data[0]);
        glGenerateMipmap(type);
        //throw std::runtime_error("Load texture failed: " + path);
    } else {
        GLenum format = mp::match(channels)(
                mp::pattern(1) = [] { return GL_RED; },
                mp::pattern(3) = [] { return GL_RGB; },
                mp::pattern(4) = [] { return GL_RGBA; }
        );
        glTexImage2D(GL_TEXTURE_2D, 0, (int) format, width, height, 0, format, GL_UNSIGNED_BYTE, bytes);
        glGenerateMipmap(type);
        stbi_image_free(bytes);
    }
    glBindTexture(type, 0);
}
