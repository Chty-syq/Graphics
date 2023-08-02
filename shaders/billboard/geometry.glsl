#version 330 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

in vec4 gColor[];

out vec2 fTexCoord;
out vec4 fColor;

uniform mat4 projection;
uniform mat4 view;
uniform vec3 cameraPos;
uniform float size;

void main() {
    vec3 position = gl_in[0].gl_Position.xyz;

    vec3 direction = normalize(cameraPos - position);
    vec3 up = vec3(0.0f, 1.0f, 0.0f);
    vec3 right = cross(direction, up);

    for(int i = 0; i < 2; ++i) {
        for(int j = 0; j < 2; ++j) {
            gl_Position = projection * view * vec4(position + ((i - 0.5) * right + j * up) * size, 1.0);
            fTexCoord = vec2(i, j);
            fColor = gColor[0];
            EmitVertex();
        }
    }
    EndPrimitive();
}
