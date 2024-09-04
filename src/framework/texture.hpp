//
// Created by chty on 23-6-29.
//
#pragma once

#include <GLFW/glfw3.h>
#include <cstdio>
#include <string>
#include <utility>
#include <stdexcept>

//class Texture2D {
//private:
//    vector<std::string> paths;
//    GLuint id{};
//    GLuint type;
//
//public:
//    explicit Texture2D(const vector<std::string>& paths, GLuint type = GL_TEXTURE_2D, bool flip = true);
//    ~Texture2D();
//    void Bind(int index) const;
//};
//
//Texture2D::Texture2D(const vector<std::string>& paths, GLuint type, bool flip): paths(paths), type(type) {
//    glGenTextures(1, &this->id);
//    glBindTexture(type, this->id);
//
//    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//    stbi_set_flip_vertically_on_load(flip);
//    for (int i = 0; i < paths.size(); ++i) {
//        int width = 50, height = 50, channels;
//        auto bytes = stbi_load(paths[i].c_str(), &width, &height, &channels, 0);
//        auto target = (type == GL_TEXTURE_2D) ? type : GL_TEXTURE_CUBE_MAP_POSITIVE_X + i;
//        if (bytes == nullptr) { //空纹理
//            std::vector<GLubyte> empty_data(width * height * 4, 0);
//            glTexImage2D(target, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, &empty_data[0]);
//            glGenerateMipmap(type);
//        } else {
//            GLenum format;
//            switch (channels) {
//                case 1: format = GL_RED; break;
//                case 3: format = GL_RGB; break;
//                case 4: format = GL_RGBA; break;
//                default: throw std::runtime_error("Unexpected channels!");
//            }
//            glTexImage2D(target, 0, (int)format, width, height, 0, format, GL_UNSIGNED_BYTE, bytes);
//            glGenerateMipmap(type);
//            stbi_image_free(bytes);
//        }
//    }
//    glBindTexture(type, 0);
//}
//
//Texture2D::~Texture2D() {
//    glDeleteTextures(1, &this->id);
//}
//
//void Texture2D::Bind(int index) const {
//    glActiveTexture(GL_TEXTURE0 + index);
//    glBindTexture(this->type, this->id);
//}
