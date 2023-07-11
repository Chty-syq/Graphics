#version 330 core

layout(location = 0) in vec3 vPosition;  //坐标
layout(location = 1) in vec2 vTexCoord;  //纹理坐标

out vec2 fTexCoord;

void main() {
    fTexCoord = vTexCoord;
    gl_Position = vec4(vPosition, 1.0);
}
