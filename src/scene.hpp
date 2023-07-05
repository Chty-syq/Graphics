//
// Created by syq on 23-7-5.
//
#pragma once
#include <common/defs.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <framework/camera.hpp>
#include <stdexcept>
#include "framework/shader.hpp"
#include "framework/sprites/floor.hpp"
#include "framework/sprites/cube.hpp"
#include "framework/texture.hpp"
#include "framework/camera.hpp"
#include "common/defs.hpp"
#include "common/utils.hpp"

#define keydown(x) (glfwGetKey(window, x) == GLFW_PRESS)

class GraphScene {
private:
    GLFWwindow* window;
    shared_ptr<Shader> normal_shader;

    static float last_frame;
    static unique_ptr<Camera> camera;
    static double last_x;
    static double last_y;

    void LoadResource();
    void Display();

    static void KeyboardInput(GLFWwindow* window);
    static void MouseMoveCallback(GLFWwindow* window, double pos_x, double pos_y);
    static void MouseScrollCallback(GLFWwindow* window, double offset_x, double offset_y);

public:
    GraphScene();
    ~GraphScene();
    void Render();
};

float GraphScene::last_frame = 0;
double GraphScene::last_x = (SCREEN_WIDTH >> 1);
double GraphScene::last_y = (SCREEN_HEIGHT >> 1);
unique_ptr<Camera> GraphScene::camera = std::make_unique<Camera>(glm::vec3(1.0f, 1.0f, 1.0f));

GraphScene::GraphScene() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    this->window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        throw std::runtime_error("Unexpected Behavior Creating GLFW Window!");
    }

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetCursorPosCallback(window, MouseMoveCallback);
    glfwSetScrollCallback(window, MouseScrollCallback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Initialize GLAD Failed!");
    }

    this->LoadResource();
}

GraphScene::~GraphScene() {
    glfwTerminate();
}

void GraphScene::LoadResource() {
    this->normal_shader = std::make_shared<Shader>(fs::current_path().parent_path() / "shaders" / "normal");
}


void GraphScene::KeyboardInput(GLFWwindow* window) {
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

void GraphScene::MouseMoveCallback(GLFWwindow* window, double pos_x, double pos_y) {
    double offset_x = pos_x - last_x;
    double offset_y = last_y - pos_y;
    camera->MouseMove((float)offset_x, (float)offset_y);
    last_x = pos_x;
    last_y = pos_y;
}

void GraphScene::MouseScrollCallback(GLFWwindow* window, double offset_x, double offset_y) {
    camera->MouseScroll((float)offset_y);
}

void GraphScene::Display() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    normal_shader->Use();
    auto view = camera->GetViewMat();
    auto projection = glm::perspective(glm::radians(camera->GetZoom()), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);
    normal_shader->SetAttribute("view", view);
    normal_shader->SetAttribute("projection", projection);
    normal_shader->SetAttribute("fLightPos", camera->GetPosition());
    normal_shader->SetAttribute("fLightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    normal_shader->SetAttribute("fViewPos", camera->GetPosition());
    normal_shader->SetAttribute("material.mAmbient", glm::vec3( 0.19225,0.19225,0.19225));
    normal_shader->SetAttribute("material.mDiffuse", glm::vec3(0.50754 ,0.50754, 0.50754));
    normal_shader->SetAttribute("material.mSpecular", glm::vec3(0.508273, 0.508273 ,0.508273));
    normal_shader->SetAttribute("material.mShininess", 0.4 * 128);

    Cube cube(normal_shader);
    Floor floor(normal_shader);

    Texture2D texture(fs::current_path().parent_path() / "assets" / "textures" / "container.jpg");
    texture.Use();

    cube.LoadData();
    cube.LoadBuffer();
    cube.Draw(glm::vec3(0.0f, 0.5f, 0.0f));

    Texture2D floor_tex(fs::current_path().parent_path() / "assets" / "textures" / "floor.jpg");
    floor_tex.Use();

    floor.LoadData();
    floor.LoadBuffer();
    floor.Draw(glm::vec3(0.0f, 0.0f, 0.0f));
}

void GraphScene::Render() {
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        this->KeyboardInput(window);
        this->Display();
        glfwSwapBuffers(window);
    }
}
