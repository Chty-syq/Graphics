#version 330 core

layout(location = 0) in vec3 vPosition;  //坐标

out vec3 fTexCoord;

uniform mat4 view;          //透视原理
uniform mat4 projection;    //投影矩阵

void main() {
    fTexCoord = vPosition;
    gl_Position = (projection * view * vec4(vPosition, 1.0)).xyww;
}
