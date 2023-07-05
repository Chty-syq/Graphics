#version 330 core

layout(location = 0) in vec3 vPosition;  //坐标
layout(location = 1) in vec2 vTexCoord;  //纹理坐标
layout(location = 2) in vec3 vNormal;    //法向量

out vec2 fTexCoord;
out vec3 fNormal;
out vec3 fPosition;

uniform mat4 model;         //变换到世界系
uniform mat4 view;          //透视原理
uniform mat4 projection;    //投影矩阵

void main() {
    gl_Position = projection * view * model * vec4(vPosition, 1.0f);
    fTexCoord = vTexCoord;
    fNormal = mat3(transpose(inverse(model))) * vNormal;
    fPosition = vec3(model * vec4(vPosition, 1.0f));
}