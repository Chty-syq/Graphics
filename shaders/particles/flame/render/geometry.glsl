#version 330 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

in float gAlpha[];
in float gSize[];
in float gLifetime[];
in float gLifespan[];

out vec2 fTexCoord;
out float fAlpha;
out float fLifetime;
out float fLifespan;

uniform mat4 projection;
uniform mat4 view;
uniform vec3 cameraPos;

void main() {
    vec3 position = gl_in[0].gl_Position.xyz;

    vec3 direction = normalize(cameraPos - position);
    vec3 up = vec3(0.0f, 1.0f, 0.0f);
    vec3 right = cross(direction, up);

    for(int i = 0; i < 2; ++i) {
        for(int j = 0; j < 2; ++j) {
            gl_Position = projection * view * vec4(position + ((i - 0.5) * right + j * up) * gSize[0], 1.0);
            fTexCoord = vec2(i, j);
            fAlpha = gAlpha[0];
            fLifetime = gLifetime[0];
            fLifespan = gLifespan[0];
            EmitVertex();
        }
    }
    EndPrimitive();
}
