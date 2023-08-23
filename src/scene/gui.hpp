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
    if (ImGui::CollapsingHeader("Fireworks")) {
        ImGui::SliderFloat("LifetimeLauncher", &SceneStatus::fireworks_lifetime_launcher, 0.0f, 10.0f);
        ImGui::SliderFloat("LifetimeShell", &SceneStatus::fireworks_lifetime_shell, 0.0f, 10.0f);
        ImGui::SliderFloat("LifetimeSecShell", &SceneStatus::fireworks_lifetime_sec_shell, 0.0f, 10.0f);
    }
    if (ImGui::CollapsingHeader("Flame")) {
        ImGui::SliderFloat("LifetimeMin", &SceneStatus::flame_lifetime_min, 0.0f, 10.0f);
        ImGui::SliderFloat("LifetimeMax", &SceneStatus::flame_lifetime_max, 0.0f, 10.0f);
        ImGui::SliderFloat3("VelocityMin", glm::value_ptr(SceneStatus::flame_velocity_min), -1.0f, 1.0f);
        ImGui::SliderFloat3("VelocityMax", glm::value_ptr(SceneStatus::flame_velocity_max), -1.0f, 1.0f);
    }
    if (ImGui::CollapsingHeader("Fountain")) {
        ImGui::SliderFloat("Radius", &SceneStatus::fountain_radius, 0.0f, 1.0f);
        ImGui::SliderAngle("Theta", &SceneStatus::fountain_theta);
        ImGui::SliderFloat("LifetimeMax", &SceneStatus::fountain_lifetime_min, 0.0f, 10.0f);
        ImGui::SliderFloat("LifetimeMin", &SceneStatus::fountain_lifetime_max, 0.0f, 10.0f);
    }

    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}