//
// Created by syq on 24-9-4.
//

#pragma once

#include "framework/textures/texture_base.hpp"

class TextureCube : public TextureBase {
private:
    vector<std::string> paths{};

public:
    explicit TextureCube(const vector<std::string> &paths, bool flip = true);
};

TextureCube::TextureCube(const vector<std::string> &paths, bool flip) : paths(paths) {
    this->type = GL_TEXTURE_CUBE_MAP;

    glGenTextures(1, &this->id);
    glBindTexture(type, this->id);

    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_set_flip_vertically_on_load(flip);

    for (int i = 0; i < paths.size(); ++i) {
        int width, height, channels;
        auto bytes = stbi_load(paths[i].c_str(), &width, &height, &channels, 0);
        if (bytes == nullptr) { //空纹理
            throw std::runtime_error("Load texture failed: " + paths[i]);
        } else {
            GLenum format = mp::match(channels)(
                    mp::pattern(1) = [] { return GL_RED; },
                    mp::pattern(3) = [] { return GL_RGB; },
                    mp::pattern(4) = [] { return GL_RGBA; }
            );
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, (int) format, width, height, 0, format, GL_UNSIGNED_BYTE, bytes);
            glGenerateMipmap(type);
            stbi_image_free(bytes);
        }
    }
    glBindTexture(type, 0);
}