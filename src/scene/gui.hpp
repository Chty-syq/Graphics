//
// Created by syq on 23-7-11.
//

#pragma once
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include "scene/status.hpp"

namespace GUI {
    void Init(GLFWwindow* window);
    void Render();
}

void GUI::Init(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    auto io = ImGui::GetIO();  (void)io;
    io.MouseDrawCursor = false;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
}

void GUI::Render() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Console");
    if (ImGui::CollapsingHeader("Lighting")) {
        ImGui::Checkbox("Blinn-Phong", &SceneStatus::blinn);
    }
    if (ImGui::CollapsingHeader("Flame")) {
        ImGui::SliderFloat("LifetimeMax", &SceneStatus::flame_lifetime_max, 0.0f, 10.0f);
        ImGui::SliderFloat("LifetimeMin", &SceneStatus::flame_lifetime_min, 0.0f, 10.0f);
    }

    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}