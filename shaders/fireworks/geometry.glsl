#version 330 core

#define PARTICLE_TYPE_LAUNCHER 0.0f
#define PARTICLE_TYPE_SHELL 1.0f
#define PARTICLE_TYPE_SEC_SHELL 2.0f

layout (points) in;
layout (points, max_vertices = 60) out;

in vec3 gPosition[];
in vec3 gVelocity[];
in vec4 gColor[];
in float gType[];
in float gLifetime[];
in float gTag[];

out vec3 fPosition;
out vec3 fVelocity;
out vec4 fColor;
out float fType;
out float fLifetime;
out float fTag;

uniform float gDeltaTime;
uniform float gTime;
uniform float gLifetimeLauncher;
uniform float gLifetimeShell;
uniform float gLifetimeSecShell;

uniform sampler1D gRandomMap;

float age = gLifetime[0] + gDeltaTime;
const float speed = 20.0f;

vec3 GetRandomDirection(float texCoord) {
    vec3 direction = texture(gRandomMap, texCoord).xyz - vec3(0.5f);
    return direction;
}

vec3 GetRandomColor(float texCoord) {
    vec3 color = texture(gRandomMap, texCoord).xyz * vec3(1.0f, 0.5f, 0.2f);
    return color;
}

void UpdateLauncher() {
    if (age >= gLifetimeLauncher) { //发射shell并重置launcher
        for(int i = 0; i < 5; ++i) {
            vec3 direction = GetRandomDirection(gTime);
            direction.y = max(direction.y, 0.5);

            fPosition = gPosition[0];
            fVelocity = normalize(direction) * speed;
            fColor = vec4(GetRandomColor(gTime), 1.0f);
            fType = PARTICLE_TYPE_SHELL;
            fLifetime = 0.0f;
            fTag = (i + 1) * 0.2f;
            EmitVertex();
            EndPrimitive();
        }
        age = 0.0f;
    }
    fPosition = gPosition[0];
    fVelocity = gVelocity[0];
    fType = PARTICLE_TYPE_LAUNCHER;
    fLifetime = age;
    fTag = gTag[0];
    EmitVertex();
    EndPrimitive();
}

void UpdateShell() {
    if (age < gLifetimeShell) { //上升
        fPosition = gPosition[0] + gDeltaTime * gVelocity[0];
        fVelocity = gVelocity[0] + gDeltaTime * vec3(0.0f, -1.81f, 0.0f);
        fColor = gColor[0];
        fType = PARTICLE_TYPE_SHELL;
        fLifetime = age;
        fTag = gTag[0];
        EmitVertex();
        EndPrimitive();
    } else { //分裂
        for(int i = 0; i < 60; ++i) {
            vec3 direction = GetRandomDirection(gTime + (i / 1000.0f) + gTag[0]);
            fPosition = gPosition[0];
            fVelocity = normalize(direction) * 2.0f;
            fColor = gColor[0];
            fType = PARTICLE_TYPE_SEC_SHELL;
            fLifetime = 0.0f;
            fTag = 0.0f;
            EmitVertex();
            EndPrimitive();
        }
    }
}

void UpdateSecShell() {
    if (age < gLifetimeSecShell) {
        fPosition = gPosition[0] + gDeltaTime * gVelocity[0];
        fVelocity = gVelocity[0] + gDeltaTime * vec3(0.0f, -9.81f, 0.0f);
        fColor = vec4(gColor[0].xyz, age / gLifetimeSecShell);
        fType = PARTICLE_TYPE_SEC_SHELL;
        fLifetime = age;
        fTag = 0.0f;
        EmitVertex();
        EndPrimitive();
    }
}

void main() {
    if (gType[0] == PARTICLE_TYPE_LAUNCHER)  UpdateLauncher();
    else if (gType[0] == PARTICLE_TYPE_SHELL)  UpdateShell();
    else if (gType[0] == PARTICLE_TYPE_SEC_SHELL)  UpdateSecShell();
}
