#version 330 core

layout(location = 0) in vec3 vPosition;  //坐标

void main() {
    gl_Position = vec4(vPosition, 1.0f);
}
