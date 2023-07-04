#version 330 core

layout(location = 0) in vec3 vPosition;  //坐标
layout(location = 1) in vec2 vTexCoord;  //纹理坐标

out vec2 fTexCoord;

uniform mat4 model; //世界系
uniform mat4 view;  //
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(vPosition, 1.0f);
    fTexCoord = vTexCoord;
}