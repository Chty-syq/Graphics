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
#include "framework/camera.hpp"
#include "framework/shader.hpp"
#include "framework/sprites/floor.hpp"
#include "framework/sprites/cube.hpp"
#include "framework/model/model.hpp"
#include "framework/texture.hpp"
#include "framework/camera.hpp"
#include "framework/game_object.hpp"
#include "framework/frame_buffer.hpp"
#include "scene/resources.hpp"
#include "scene/scene.hpp"
#include "scene/cursor.hpp"
#include "common/defs.hpp"

#define keydown(x) (glfwGetKey(window, x) == GLFW_PRESS)

namespace GraphRender {
    GLFWwindow* window;
    unique_ptr<Camera> camera = std::make_unique<Camera>(glm::vec3(1.0f, 1.0f, 1.0f));
    unique_ptr<FrameBuffer> frame_buffer = std::make_unique<FrameBuffer>();

    float last_frame = 0;
    int window_pos_x;
    int window_pos_y;

    bool blinn = false;

    shared_ptr<CursorManager> cursor = std::make_shared<CursorManager>();

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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        throw std::runtime_error("Unexpected Behavior Creating GLFW Window!");
    }

    glfwGetWindowPos(window, &window_pos_x, &window_pos_y);
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    glfwSetKeyCallback(window, KeyboardCallback);
    glfwSetCursorPosCallback(window, MouseMoveCallback);
    glfwSetScrollCallback(window, MouseScrollCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Initialize GLAD Failed!");
    }

    ResourceManager::Init();
    GraphScene::LoadScene();
    frame_buffer->Init();
}

void GraphRender::KeyboardInput() {
    auto cur_frame = (float)glfwGetTime();
    auto duration = cur_frame - last_frame;
    if (keydown(GLFW_KEY_W))  camera->KeyboardInput(Direction::forward, duration);
    if (keydown(GLFW_KEY_S))  camera->KeyboardInput(Direction::backward, duration);
    if (keydown(GLFW_KEY_A))  camera->KeyboardInput(Direction::left, duration);
    if (keydown(GLFW_KEY_D))  camera->KeyboardInput(Direction::right, duration);
    if (keydown(GLFW_KEY_Q))  camera->KeyboardInput(Direction::up, duration);
    if (keydown(GLFW_KEY_E))  camera->KeyboardInput(Direction::down, duration);

    if (keydown(GLFW_KEY_ESCAPE)) glfwSetWindowShouldClose(window, true);
    last_frame = cur_frame;
}

void GraphRender::KeyboardCallback(GLFWwindow* window_, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_B && action == GLFW_PRESS) {
        ResourceManager::shader_object->Use();
        ResourceManager::shader_object->SetAttribute("blinn", blinn = !blinn);
    }
}

void GraphRender::MouseMoveCallback(GLFWwindow* window_, double pos_x, double pos_y) {
    int center_pos_x = window_pos_x + (int)(SCREEN_WIDTH >> 1);
    int center_pos_y = window_pos_y + (int)(SCREEN_HEIGHT >> 1);
    double offset_x = pos_x - (SCREEN_WIDTH >> 1);
    double offset_y = (SCREEN_HEIGHT >> 1) - pos_y;
    camera->MouseMove((float)offset_x, (float)offset_y);
    cursor->SetCursorPosLinux(center_pos_x, center_pos_y);
}

void GraphRender::MouseScrollCallback(GLFWwindow* window_, double offset_x, double offset_y) {
    camera->MouseScroll((float)offset_y);
}

void GraphRender::Display() {
    frame_buffer->Bind();
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_FRAMEBUFFER_SRGB); //gamma校正
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto view = camera->GetViewMat();
    auto projection = glm::perspective(glm::radians(camera->GetZoom()), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);
    ResourceManager::shader_object->Use();
    ResourceManager::shader_object->SetAttribute("view", view);
    ResourceManager::shader_object->SetAttribute("projection", projection);
    ResourceManager::shader_object->SetAttribute("fLightSpot.sDirection", camera->GetFront());
    ResourceManager::shader_object->SetAttribute("fLightSpot.sLightPoint.pPosition", camera->GetPosition());

    ResourceManager::shader_skybox->Use();
    ResourceManager::shader_skybox->SetAttribute("view", glm::mat4(glm::mat3(view)));
    ResourceManager::shader_skybox->SetAttribute("projection", projection);

    GraphScene::DrawSkybox();
    GraphScene::DrawScene();

    frame_buffer->Render();
}

void GraphRender::Render() {
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        KeyboardInput();
        Display();
        glfwSwapBuffers(window);
    }
    glfwTerminate();
}
