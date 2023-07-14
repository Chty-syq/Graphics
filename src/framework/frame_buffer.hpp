//
// Created by syq on 23-7-11.
//

#pragma once
#include <stdexcept>
#include "framework/sprites/2D/square.hpp"

class FrameBuffer {
private:
    GLuint fbo{};
    GLuint rbo{};
    GLuint color_texture{};
    shared_ptr<Square> square;
    void GenerateColorAttachment();
    void GenerateRenderBuffer();
public:
    FrameBuffer();
    ~FrameBuffer();
    void Init();
    void Bind() const;
    void Render() const;
};

FrameBuffer::FrameBuffer() = default;

FrameBuffer::~FrameBuffer() {
    glDeleteTextures(1, &color_texture);
    glDeleteRenderbuffers(1, &rbo);
    glDeleteFramebuffers(1, &fbo);
}

void FrameBuffer::Init() {
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    this->GenerateColorAttachment();
    this->GenerateRenderBuffer();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->color_texture, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        throw std::runtime_error("Uncompleted Framebuffer!");
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    this->square = std::make_shared<Square>();
    this->square->LoadData();
    this->square->LoadBuffer();
}

void FrameBuffer::GenerateColorAttachment() {
    glGenTextures(1, &color_texture);
    glBindTexture(GL_TEXTURE_2D, color_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void FrameBuffer::GenerateRenderBuffer() {
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void FrameBuffer::Bind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void FrameBuffer::Render() const {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
    ResourceManager::shader_screen->Use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->color_texture);
    this->square->Render();
}
