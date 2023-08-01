#version 330 core

in vec2 fTexCoord;

out vec4 color;

uniform sampler2D fTexture;

void main() {
    color = texture(fTexture, fTexCoord);
    if (color.r >= 0.9f && color.g >= 0.9f && color.b >= 0.9f) {
        discard;
    }
}
