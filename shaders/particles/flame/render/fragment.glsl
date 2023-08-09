#version 330 core

in vec2 fTexCoord;
in float fAlpha;
in float fLifetime;
in float fLifespan;

out vec4 color;

uniform sampler2D fFlameStart;
uniform sampler2D fFlameSpark;

void main() {
    if (fLifetime / fLifespan < 0.4f) {
        color = texture(fFlameStart, fTexCoord);
    } else {
        color = texture(fFlameSpark, fTexCoord);
    }
    if (all(lessThan(color.rgb, vec3(0.1f))) || color.a < 0.2f) {
        discard;
    }
    color = vec4(0.5f, 0.3f, 0.1f, fAlpha);
}
