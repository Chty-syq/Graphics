//
// Created by syq on 23-7-12.
//

#pragma once
#include "common/defs.hpp"

class DepthBuffer {
private:
    GLuint fbo{};
    shared_ptr<Square> square;
    void GenerateDepthAttachment();
public:
    GLuint depth_texture{};
    DepthBuffer();
    ~DepthBuffer();
    void Init();
    void Bind() const;
    void Render();
};

DepthBuffer::DepthBuffer() = default;

DepthBuffer::~DepthBuffer() {
    glDeleteTextures(1, &depth_texture);
    glDeleteFramebuffers(1, &fbo);
}


void DepthBuffer::Init() {
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    this->GenerateDepthAttachment();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_texture, 0);
    glDrawBuffer(GL_NONE);   //不需要渲染
    glReadBuffer(GL_NONE);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        throw std::runtime_error("Uncompleted Framebuffer!");
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    this->square = std::make_shared<Square>();
    this->square->LoadData();
    this->square->LoadBuffer();
}

void DepthBuffer::GenerateDepthAttachment() {
    glGenTextures(1, &depth_texture);
    glBindTexture(GL_TEXTURE_2D, depth_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT,nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    GLfloat border_color[] = {1.0, 1.0, 1.0, 1.0};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border_color);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void DepthBuffer::Bind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void DepthBuffer::Render() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
    ResourceManager::shader_screen->Use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->depth_texture);
    this->square->Render();
}

