#version 330 core

layout(location = 0) in vec3 vPosition;  //坐标

uniform mat4 model;
uniform mat4 mLightSpace;

void main() {
    gl_Position = mLightSpace * model * vec4(vPosition, 1.0f);
}
