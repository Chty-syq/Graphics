#version 330 core

layout(location = 0) in vec3 vPosition;  //坐标
layout(location = 1) in vec4 vColor;

out vec4 gColor;

void main() {
    gl_Position = vec4(vPosition, 1.0f);
    gColor = vColor;
}
