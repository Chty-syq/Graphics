#define GLEW_STATIC
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <filesystem>
#include "framework/shader.hpp"
#include "framework/sprites/square.hpp"
#include "framework/sprites/cube.hpp"
#include "framework/texture.hpp"
#include "framework/camera.hpp"
#include "common/defs.hpp"
#include "common/utils.hpp"

#define keydown(x) (glfwGetKey(window, x) == GLFW_PRESS)

namespace fs = std::filesystem;

float last_frame;
double last_x = (SCREEN_WIDTH >> 1);
double last_y = (SCREEN_HEIGHT >> 1);
Camera camera(glm::vec3(1.0f, 1.0f, 1.0f));

void display() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Shader shader(fs::current_path().parent_path() / "shaders" / "object");
    shader.Use();
    auto view = camera.GetViewMat();
    auto projection = glm::perspective(glm::radians(camera.GetZoom()), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);
    shader.SetAttribute("view", view);
    shader.SetAttribute("projection", projection);

    Cube cube(shader);
    Texture2D texture(fs::current_path().parent_path() / "assets" / "container.jpg");

    texture.Use();

    cube.LoadData();
    cube.LoadBuffer();
    cube.Draw(
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(1.0f, 1.0f, 1.0f),
            glm::vec3(glm::radians(50.0f) * glfwGetTime(), glm::radians(50.0f) * glfwGetTime(), 0.0f)
            );
}

void keyboard_input(GLFWwindow* window) {
    auto cur_frame = (float)glfwGetTime();
    auto duration = cur_frame - last_frame;
    if (keydown(GLFW_KEY_W))  camera.KeyboardInput(Direction::forward, duration);
    if (keydown(GLFW_KEY_S))  camera.KeyboardInput(Direction::backward, duration);
    if (keydown(GLFW_KEY_A))  camera.KeyboardInput(Direction::left, duration);
    if (keydown(GLFW_KEY_D))  camera.KeyboardInput(Direction::right, duration);
    if (keydown(GLFW_KEY_Q))  camera.KeyboardInput(Direction::up, duration);
    if (keydown(GLFW_KEY_E))  camera.KeyboardInput(Direction::down, duration);
    last_frame = cur_frame;
}

void mouse_move_callback(GLFWwindow* window, double pos_x, double pos_y) {
    double offset_x = pos_x - last_x;
    double offset_y = last_y - pos_y;
    camera.MouseMove((float)offset_x, (float)offset_y);
    last_x = pos_x;
    last_y = pos_y;
}

void mouse_scroll_callback(GLFWwindow* window, double offset_x, double offset_y) {
    camera.MouseScroll((float)offset_y);
}


int main() {
    utils::SetCursorPosLinux(0, 0);
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    auto window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetCursorPosCallback(window, mouse_move_callback);
    glfwSetScrollCallback(window, mouse_scroll_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        keyboard_input(window);
        display();
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}
