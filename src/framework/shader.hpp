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
#include "common/structs.hpp"

class Shader {
private:
    GLuint program;
    static std::string LoadGLSLCode(const std::string& path);
    static void LoadShader(GLuint shader_id, const std::string& path);
    void LoadProgram(GLuint v_shader_id, GLuint f_shader_id) const;
    void LoadProgram(GLuint v_shader_id, GLuint f_shader_id, GLuint g_shader_id) const;
    void LinkProgram() const;

public:
    explicit Shader(const std::string& path);
    ~Shader() = default;
    void Use() const;
    void SetTFOVarying(const vector<std::string>& names);
    void SetAttribute(const std::string &name, int value) const;
    void SetAttribute(const std::string &name, float value) const;
    void SetAttribute(const std::string &name, const glm::vec3 &value) const;
    void SetAttribute(const std::string &name, const glm::mat4 &value) const;
    void SetLightParal(LightParal light) const;
    void SetLightPoint(LightPoint light, int index) const;
    void SetLightSpot(LightSpot light) const;
};

Shader::Shader(const std::string& path) {
    program = glCreateProgram();
    fs::path v_shader_path(path + "/vertex.glsl");
    fs::path f_shader_path(path + "/fragment.glsl");
    fs::path g_shader_path(path + "/geometry.glsl");
    if (!exists(v_shader_path) || !exists(f_shader_path)) {
        throw std::runtime_error("[ERROR] Unexpected shader path!");
    }
    auto v_shader_id = glCreateShader(GL_VERTEX_SHADER);
    auto f_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    LoadShader(v_shader_id, v_shader_path);
    LoadShader(f_shader_id, f_shader_path);

    if (exists(g_shader_path)) {
        auto g_shader_id = glCreateShader(GL_GEOMETRY_SHADER);
        LoadShader(g_shader_id, g_shader_path);
        LoadProgram(v_shader_id, f_shader_id, g_shader_id);
    }
    else {
        LoadProgram(v_shader_id, f_shader_id);
    }

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

void Shader::LoadProgram(GLuint v_shader_id, GLuint f_shader_id) const {
    glAttachShader(program, v_shader_id);
    glAttachShader(program, f_shader_id);
    glDeleteShader(v_shader_id);
    glDeleteShader(f_shader_id);
    this->LinkProgram();
}

void Shader::LoadProgram(GLuint v_shader_id, GLuint f_shader_id, GLuint g_shader_id) const {
    glAttachShader(program, g_shader_id);
    glDeleteShader(g_shader_id);
    LoadProgram(v_shader_id, f_shader_id);
}

void Shader::LinkProgram() const {
    int success;
    char infoLog[512];
    glLinkProgram(program);
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

void Shader::SetLightParal(LightParal light) const {
    this->SetAttribute("fLightParal.pDirection", light.direction);
    this->SetAttribute("fLightParal.pFactor.fAmbient", light.factor.ambient);
    this->SetAttribute("fLightParal.pFactor.fDiffuse", light.factor.diffuse);
    this->SetAttribute("fLightParal.pFactor.fSpecular", light.factor.specular);
}

void Shader::SetLightPoint(LightPoint light, int index) const {
    this->SetAttribute("fLightPoint[" + std::to_string(index) + "].pPosition", light.position);
    this->SetAttribute("fLightPoint[" + std::to_string(index) + "].pCoefficient", light.coefficient);
    this->SetAttribute("fLightPoint[" + std::to_string(index) + "].pFactor.fAmbient", light.factor.ambient);
    this->SetAttribute("fLightPoint[" + std::to_string(index) + "].pFactor.fDiffuse", light.factor.diffuse);
    this->SetAttribute("fLightPoint[" + std::to_string(index) + "].pFactor.fSpecular", light.factor.specular);
}

void Shader::SetLightSpot(LightSpot light) const {
    this->SetAttribute("fLightSpot.sCutoffInner", light.cutoff_inner);
    this->SetAttribute("fLightSpot.sCutoffOuter", light.cutoff_outer);
    this->SetAttribute("fLightSpot.sLightPoint.pCoefficient", light.light_point.coefficient);
    this->SetAttribute("fLightSpot.sLightPoint.pFactor.fAmbient", light.light_point.factor.ambient);
    this->SetAttribute("fLightSpot.sLightPoint.pFactor.fDiffuse", light.light_point.factor.diffuse);
    this->SetAttribute("fLightSpot.sLightPoint.pFactor.fSpecular", light.light_point.factor.specular);
}

void Shader::SetTFOVarying(const vector<std::string>& names) {
    vector<char*> varyings;
    for(const auto & name : names) {
        varyings.push_back(const_cast<char*>(name.c_str()));
    }
    glTransformFeedbackVaryings(this->program, (int)varyings.size(), &varyings[0], GL_INTERLEAVED_ATTRIBS);
    this->LinkProgram();
}
