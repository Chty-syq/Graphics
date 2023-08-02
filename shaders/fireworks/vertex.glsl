#version 330 core

layout(location = 0) in vec3 vPosition;  //坐标
layout(location = 1) in vec3 vVelocity;  //速度
layout(location = 2) in vec4 vColor;
layout(location = 3) in float vType;
layout(location = 4) in float vLifetime;
layout(location = 5) in float vTag;

out vec3 gPosition;
out vec3 gVelocity;
out vec4 gColor;
out float gType;
out float gLifetime;
out float gTag;

void main() {
    gPosition = vPosition;
    gVelocity = vVelocity;
    gColor = vColor;
    gType = vType;
    gLifetime = vLifetime;
    gTag = vTag;
}
