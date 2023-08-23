//
// Created by syq on 23-7-5.
//
#pragma once
#define GLEW_STATIC
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <filesystem>
#include <stdexcept>
#include "common/defs.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "framework/camera.hpp"
#include "framework/shader.hpp"
#include "framework/model/model.hpp"
#include "framework/texture.hpp"
#include "framework/camera.hpp"
#include "framework/game_object.hpp"
#include "framework/frame_buffer.hpp"
#include "framework/depth_buffer.hpp"
#include "framework/billboard.hpp"
#include "scene/resources.hpp"
#include "scene/scene.hpp"
#include "scene/gui.hpp"
#include "scene/status.hpp"
#include "common/defs.hpp"

#define keydown(x) (glfwGetKey(window, x) == GLFW_PRESS)

namespace GraphRender {
    GLFWwindow* window;
    shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3(1.0f, 1.0f, 1.0f));
    unique_ptr<FrameBuffer> frame_buffer = std::make_unique<FrameBuffer>();
    unique_ptr<DepthBuffer> depth_buffer = std::make_unique<DepthBuffer>();

    OperateMode mode = OperateMode::roaming;

    void UpdateStateBegin();
    void UpdateStateEnd();
    void Display();
    void KeyboardInput();
    void KeyboardCallback(GLFWwindow* window_, int key, int scancode, int action, int mods);
    void MouseMoveCallback(GLFWwindow* window_, double pos_x, double pos_y);
    void MouseScrollCallback(GLFWwindow* window_, double offset_x, double offset_y);

    void Init();
    void Render();
}

void GraphRender::Init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        throw std::runtime_error("Unexpected Behavior Creating GLFW Window!");
    }

    glfwMakeContextCurrent(window);
    switch (mode) {
        case roaming: glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); break;
        case control: glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); break;
    }
    glfwSetKeyCallback(window, KeyboardCallback);
    glfwSetCursorPosCallback(window, MouseMoveCallback);
    glfwSetScrollCallback(window, MouseScrollCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Initialize GLAD Failed!");
    }

    ResourceManager::Init();
    GraphScene::LoadScene();
    frame_buffer->Init();
    depth_buffer->Init();
}

void GraphRender::KeyboardInput() {
    float duration = SceneStatus::GetDuration();
    if (keydown(GLFW_KEY_W))  camera->KeyboardInput(Direction::forward, duration);
    if (keydown(GLFW_KEY_S))  camera->KeyboardInput(Direction::backward, duration);
    if (keydown(GLFW_KEY_A))  camera->KeyboardInput(Direction::left, duration);
    if (keydown(GLFW_KEY_D))  camera->KeyboardInput(Direction::right, duration);
    if (keydown(GLFW_KEY_Q))  camera->KeyboardInput(Direction::up, duration);
    if (keydown(GLFW_KEY_E))  camera->KeyboardInput(Direction::down, duration);

    if (keydown(GLFW_KEY_ESCAPE)) glfwSetWindowShouldClose(window, true);
}

void GraphRender::KeyboardCallback(GLFWwindow* window_, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_LEFT_ALT || key == GLFW_KEY_RIGHT_ALT && action == GLFW_PRESS) {
        switch (mode) {
            case roaming:
                mode = OperateMode::control;
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                break;
            case control:
                mode = OperateMode::roaming;
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                break;
        }
    }
}

void GraphRender::MouseMoveCallback(GLFWwindow* window_, double pos_x, double pos_y) {
    static double last_x = 0.0, last_y = 0.0;
    static bool is_first = true;
    if (mode == OperateMode::roaming) {
        if (is_first) {
            last_x = pos_x;
            last_y = pos_y;
            is_first = false;
        }
        double offset_x = pos_x - last_x;
        double offset_y = last_y - pos_y;
        camera->MouseMove((float)offset_x, (float)offset_y);
        last_x = pos_x;
        last_y = pos_y;
    } else {
        is_first = true;
    }
}

void GraphRender::MouseScrollCallback(GLFWwindow* window_, double offset_x, double offset_y) {
    camera->MouseScroll((float)offset_y);
}

void GraphRender::UpdateStateBegin() {
    SceneStatus::current_time = (float)glfwGetTime();
    float duration = SceneStatus::GetDuration();

    static float timer = 0.0f;
    static int frames = 0;
    if (++frames && (timer += duration) > 1.0f) {
        SceneStatus::fps = frames;
        timer -= 1.0f;
        frames = 0;
    }
    auto title = "Graphic - " + std::to_string(SceneStatus::fps) + "FPS";
    glfwSetWindowTitle(window, title.c_str());
}

void GraphRender::UpdateStateEnd() {
    SceneStatus::previous_time = SceneStatus::current_time;
}

void GraphRender::Display() {
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_FRAMEBUFFER_SRGB); //gamma校正

    //depth_buffer
    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    depth_buffer->Bind();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glCullFace(GL_FRONT);
    GraphScene::RenderObjects(ResourceManager::shader_depth);
    glCullFace(GL_BACK);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, depth_buffer->depth_texture);

    //color_buffer
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    frame_buffer->Bind();
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ResourceManager::SetShaderProperties(camera);

    GraphScene::RenderSkybox(ResourceManager::shader_skybox);
    GraphScene::RenderObjects(ResourceManager::shader_object);
    //GraphScene::RenderBillBoard(ResourceManager::shader_billboard);
    GraphScene::RenderParticleSystem();

    //depth_buffer->Render();
    frame_buffer->Render();
}

void GraphRender::Render() {
    while(!glfwWindowShouldClose(window))
    {
        UpdateStateBegin();
        glfwPollEvents();
        KeyboardInput();
        Display();
        if (mode == OperateMode::control) {
            GUI::Render();
        }
        glfwSwapBuffers(window);
        UpdateStateEnd();
    }
    glfwTerminate();
}
