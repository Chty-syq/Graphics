#define GLEW_STATIC
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <filesystem>
#include "scene.hpp"

int main() {
    GraphScene scene;
    scene.Render();
    return 0;
}
