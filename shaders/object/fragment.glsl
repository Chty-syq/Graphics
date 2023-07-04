#version 330 core

in vec2 fTexCoord;   //纹理坐标

out vec4 color;

uniform sampler2D fTexture;  //纹理

void main() {
    color = texture(fTexture, fTexCoord);
}
