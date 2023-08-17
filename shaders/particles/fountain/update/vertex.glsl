#version 330 core

layout(location = 0) in vec3 vPosition;  //坐标
layout(location = 1) in vec3 vVelocity;  //速度
layout(location = 2) in float vType;
layout(location = 3) in float vLifetime;

out vec3 gPosition;
out vec3 gVelocity;
out float gType;
out float gLifetime;

void main() {
    gPosition = vPosition;
    gVelocity = vVelocity;
    gType = vType;
    gLifetime = vLifetime;
}
