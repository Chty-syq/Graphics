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

namespace fs = std::filesystem;

const GLuint WIDTH = 800, HEIGHT = 600;

void display(Shader shader) {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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


int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    auto window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    Shader shader(fs::current_path().parent_path() / "shaders" / "object");
    shader.Use();
    auto view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
    auto projection = glm::perspective(glm::radians(45.0f), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
    shader.SetAttribute("view", view);
    shader.SetAttribute("projection", projection);

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        display(shader);
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}
