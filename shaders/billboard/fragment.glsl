#version 330 core

in vec2 fTexCoord;

out vec4 color;

uniform sampler2D fTexture;

void main() {
    color = texture(fTexture, fTexCoord);
    if (all(lessThan(color.rgb, vec3(0.1f))) || all(greaterThan(color.rgb, vec3(0.9f))) || color.a < 0.2f) {
        discard;
    }
}
