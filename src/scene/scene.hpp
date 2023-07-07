//
// Created by syq on 23-7-5.
//
#pragma once
#include "common/defs.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "framework/camera.hpp"
#include <stdexcept>
#include "framework/shader.hpp"
#include "framework/sprites/floor.hpp"
#include "framework/sprites/cube.hpp"
#include "framework/model/model.hpp"
#include "framework/texture.hpp"
#include "framework/camera.hpp"
#include "scene/resources.hpp"
#include "common/defs.hpp"
#include "common/utils.hpp"

#define keydown(x) (glfwGetKey(window, x) == GLFW_PRESS)

namespace GraphScene {
    GLFWwindow* window;
    vector<shared_ptr<BaseSprite>> sprites;
    vector<shared_ptr<Model>> models;
    unique_ptr<Camera> camera = std::make_unique<Camera>(glm::vec3(1.0f, 1.0f, 1.0f));

    float last_frame = 0;
    int window_pos_x;
    int window_pos_y;

    void Init();
    void LoadSceneObjects();

    void DrawSkybox();
    void Display();

    void KeyboardInput();
    void MouseMoveCallback(GLFWwindow* window_, double pos_x, double pos_y);
    void MouseScrollCallback(GLFWwindow* window_, double offset_x, double offset_y);

    void Render();
};

void GraphScene::Init() {
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

    glfwSetCursorPosCallback(window, MouseMoveCallback);
    glfwSetScrollCallback(window, MouseScrollCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Initialize GLAD Failed!");
    }

    ResourceManager::Init();
    LoadSceneObjects();
}

void GraphScene::LoadSceneObjects() {
    auto cube = std::make_shared<Cube>();
    auto floor = std::make_shared<Floor>();
    sprites.push_back(cube);
    sprites.push_back(floor);

    auto nanosuit = std::make_shared<Model>(fs::current_path().parent_path() / "assets" / "meshes" / "nanosuit" / "nanosuit.obj");
    auto klee = std::make_shared<Model>(fs::current_path().parent_path() / "assets" / "meshes" / "Klee" / "Klee.pmx");
    models.push_back(nanosuit);
    models.push_back(klee);
}

void GraphScene::KeyboardInput() {
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

void GraphScene::MouseMoveCallback(GLFWwindow* window_, double pos_x, double pos_y) {
    int center_pos_x = window_pos_x + (int)(SCREEN_WIDTH >> 1);
    int center_pos_y = window_pos_y + (int)(SCREEN_HEIGHT >> 1);
    double offset_x = pos_x - (SCREEN_WIDTH >> 1);
    double offset_y = (SCREEN_HEIGHT >> 1) - pos_y;
    camera->MouseMove((float)offset_x, (float)offset_y);
    utils::SetCursorPosLinux(center_pos_x, center_pos_y);
}

void GraphScene::MouseScrollCallback(GLFWwindow* window_, double offset_x, double offset_y) {
    camera->MouseScroll((float)offset_y);
}

void GraphScene::DrawSkybox() {
    glDepthFunc(GL_LEQUAL);
    Cube skybox("skybox");
    skybox.LoadData();
    skybox.LoadBuffer();
    skybox.Draw(ResourceManager::shader_skybox, glm::vec3(0.0f));
    glDepthFunc(GL_LESS);
}

void GraphScene::Display() {
    glEnable(GL_DEPTH_TEST);
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
    DrawSkybox();

    Floor floor("floor");
    Cube cube("container", "container_spec");

    cube.LoadData();
    cube.LoadBuffer();
    cube.Draw(ResourceManager::shader_object, glm::vec3(5.0f, 0.5f, 5.0f));

    floor.LoadData();
    floor.LoadBuffer();
    floor.Draw(ResourceManager::shader_object, glm::vec3(0.0f, 0.0f, 0.0f));

    //this->models[0]->Draw(ResourceManager::shader_object, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.1f));
    models[1]->Draw(ResourceManager::shader_object, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.1f));
}

void GraphScene::Render() {
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        KeyboardInput();
        Display();
        glfwSwapBuffers(window);
    }
    glfwTerminate();
}
