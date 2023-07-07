#version 330 core

in vec3 fTexCoord;   //纹理坐标

out vec4 color;

uniform samplerCube fSkybox;   //天空盒

void main() {
    color = texture(fSkybox, fTexCoord);
}
