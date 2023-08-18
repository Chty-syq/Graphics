//
// Created by chty on 23-7-3.
//
#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include <GLFW/glfw3.h>
#include <cstdio>
#include <memory>
#include <iostream>
#include <vector>
#include <map>
#include <stb_image.h>
#include "common/structs.hpp"

namespace fs = std::filesystem;

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::pair;
using std::unique_ptr;
using std::shared_ptr;

using VertexArr = std::vector<Vertex>;
using IndiceArr = std::vector<GLuint>;

const float PI = (float)acos(-1);

const GLuint SCREEN_WIDTH = 1920;
const GLuint SCREEN_HEIGHT = 1080;

const GLuint SHADOW_WIDTH = 1024;
const GLuint SHADOW_HEIGHT = 1024;

const float CAMERA_PITCH = 0.0;
const float CAMERA_YAW = -90.0;
const float CAMERA_SPEED = 3.0;
const float CAMERA_SENSITIVITY = 0.1;
const float CAMERA_ZOOM = 45.0;

const GLuint PARTICLE_NUM = 18000;


enum Direction {
    forward, backward, left, right, up, down
};

enum OperateMode {
    roaming, control
};
