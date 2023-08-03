#version 330 core

layout(location = 0) in vec3 vPosition;  //坐标
layout(location = 1) in float vAlpha;
layout(location = 2) in float vSize;
layout(location = 3) in float vLifetime;
layout(location = 4) in float vLifespan;

out float gAlpha;
out float gSize;
out float gLifetime;
out float gLifespan;

void main() {
    gl_Position = vec4(vPosition, 1.0f);
    gAlpha = vAlpha;
    gSize = vSize;
    gLifetime = vLifetime;
    gLifespan = vLifespan;
}
