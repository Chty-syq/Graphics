//
// Created by chty on 23-6-8.
//
#pragma once
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <utility>
#include "glm/gtc/type_ptr.hpp"

class Shader {
private:
    GLuint program;
    GLuint v_shader_id;
    GLuint f_shader_id;
    static std::string LoadGLSLCode(const std::string& path);
    static void LoadShader(GLuint shader_id, const std::string& path);
    void LoadProgram() const;

public:
    explicit Shader(const std::string& path);
    ~Shader() = default;
    void Use() const;
    void SetAttribute(const std::string &name, int value) const;
    void SetAttribute(const std::string &name, float value) const;
    void SetAttribute(const std::string &name, const glm::vec3 &value) const;
    void SetAttribute(const std::string &name, const glm::mat4 &value) const;
};

Shader::Shader(const std::string& path) {
    program = glCreateProgram();
    v_shader_id = glCreateShader(GL_VERTEX_SHADER);
    f_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    LoadShader(v_shader_id, path + "/vertex.glsl");
    LoadShader(f_shader_id, path + "/fragment.glsl");
    LoadProgram();
}

std::string Shader::LoadGLSLCode(const std::string& path) {
    std::ifstream shader_file;
    shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        shader_file.open(path);
        std::stringstream stream;
        stream << shader_file.rdbuf();
        shader_file.close();
        return stream.str();
    } catch (std::ifstream::failure &e) {
        std::cerr << "[Error] read shader file" << std::endl;
    }
    return "";
}

void Shader::LoadShader(GLuint shader_id, const std::string& path) {
    auto code = LoadGLSLCode(path);
    auto code_ptr = code.c_str();
    glShaderSource(shader_id, 1, &code_ptr, nullptr);
    glCompileShader(shader_id);

    int success;
    char infoLog[512];
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader_id, 512, nullptr, infoLog);
        std::cout << "[Error] shader compile failed!" << std::endl;
        std::cout << infoLog << std::endl;
        return;
    }
}

void Shader::LoadProgram() const {
    glAttachShader(program, v_shader_id);
    glAttachShader(program, f_shader_id);
    glDeleteShader(v_shader_id);
    glDeleteShader(f_shader_id);
    glLinkProgram(program);

    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "[Error] shader program compile failed!" << std::endl;
        std::cerr << infoLog << std::endl;
        return;
    }
}

void Shader::Use() const {
    glUseProgram(this->program);
}

void Shader::SetAttribute(const std::string &name, int value) const {
    auto location = glGetUniformLocation(program, name.c_str());
    glUniform1i(location, value);
}

void Shader::SetAttribute(const std::string &name, float value) const {
    auto location = glGetUniformLocation(program, name.c_str());
    glUniform1f(location, value);
}

void Shader::SetAttribute(const std::string &name, const glm::vec3 &value) const {
    auto location = glGetUniformLocation(program, name.c_str());
    glUniform3f(location, value.x, value.y, value.z);
}

void Shader::SetAttribute(const std::string &name, const glm::mat4 &value) const {
    auto location = glGetUniformLocation(program, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}
