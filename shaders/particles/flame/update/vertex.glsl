#version 330 core

layout(location = 0) in vec3 vPosition;  //坐标
layout(location = 1) in vec3 vVelocity;  //速度
layout(location = 2) in float vAlpha;
layout(location = 3) in float vType;
layout(location = 4) in float vSize;
layout(location = 5) in float vLifetime;
layout(location = 6) in float vLifespan;

out vec3 gPosition;
out vec3 gVelocity;
out float gAlpha;
out float gType;
out float gSize;
out float gLifetime;
out float gLifespan;

void main() {
    gPosition = vPosition;
    gVelocity = vVelocity;
    gAlpha = vAlpha;
    gType = vType;
    gSize = vSize;
    gLifetime = vLifetime;
    gLifespan = vLifespan;
}
