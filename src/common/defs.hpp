//
// Created by chty on 23-7-3.
//
#pragma once
#include <GLFW/glfw3.h>
#include <cstdio>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

using GLfloatVec = std::vector<GLfloat>;
using GLuintVec = std::vector<GLuint>;

const GLuint SCREEN_WIDTH = 800;
const GLuint SCREEN_HEIGHT = 600;

const float CAMERA_PITCH = 0.0;
const float CAMERA_YAW = -90.0;
const float CAMERA_SPEED = 2.5;
const float CAMERA_SENSITIVITY = 0.1;
const float CAMERA_ZOOM = 45.0;

enum Direction {
    forward, backward, left, right, up, down
};
