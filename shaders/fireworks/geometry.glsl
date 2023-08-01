#version 330 core

#define PARTICLE_TYPE_LAUNCHER 0.0f
#define PARTICLE_TYPE_SHELL 1.0f
#define PARTICLE_TYPE_SEC_SHELL 2.0f

layout (points) in;
layout (points, max_vertices = 30) out;

in vec3 gPosition[];
in vec3 gVelocity[];
in float gType[];
in float gLifetime[];

out vec3 fPosition;
out vec3 fVelocity;
out float fType;
out float fLifetime;

uniform float gDeltaTime;
uniform float gTime;
uniform float gLifetimeLauncher;
uniform float gLifetimeShell;
uniform float gLifetimeSecShell;

uniform sampler1D gRandomMap;

float age = gLifetime[0] + gDeltaTime;

vec3 GetRandomDirection(float texCoord) {
    vec3 direction = texture(gRandomMap, texCoord).xyz - vec3(0.5f);
    return direction;
}

void UpdateLauncher() {
    if (age >= gLifetimeLauncher) { //产生shell并重置launcher
        vec3 direction = GetRandomDirection(gTime / 1000.0);
        direction.y = max(direction.y, 0.5);

        fPosition = gPosition[0];
        //fVelocity = normalize(direction) * 20.0f;
        fVelocity = vec3(0.0f, 1.0f, 0.0f) * 20.f;
        fType = PARTICLE_TYPE_SHELL;
        fLifetime = 0.0f;
        EmitVertex();
        EndPrimitive();

        age = 0.0f;
    }
    fPosition = gPosition[0];
    fVelocity = gVelocity[0];
    fType = PARTICLE_TYPE_LAUNCHER;
    fLifetime = age;
    EmitVertex();
    EndPrimitive();
}

void UpdateShell() {
    if (age < gLifetimeShell) { //上升
        fPosition = gPosition[0] + gDeltaTime / 1000.0f * gVelocity[0];
        fVelocity = gVelocity[0] + gDeltaTime / 1000.0f * vec3(0.0f, -10.0f, 0.0f);
        fType = PARTICLE_TYPE_SHELL;
        fLifetime = age;
        EmitVertex();
        EndPrimitive();
    } else { //分裂
        for(int i = 0; i < 10; ++i) {
            vec3 direction = GetRandomDirection((gTime + i) / 1000.0);
            fPosition = gPosition[0];
            fVelocity = normalize(direction) * 20.0f;
            fType = PARTICLE_TYPE_SEC_SHELL;
            fLifetime = 0.0f;
            EmitVertex();
            EndPrimitive();
        }
    }
}

void UpdateSecShell() {
    if (age < gLifetimeSecShell) {
        fPosition = gPosition[0] + gDeltaTime / 1000.0f * gVelocity[0];
        fVelocity = gVelocity[0] + gDeltaTime / 1000.0f * vec3(0.0f, -9.81f, 0.0f);
        fType = PARTICLE_TYPE_SEC_SHELL;
        fLifetime = age;
        EmitVertex();
        EndPrimitive();
    }
}

void main() {
    if (gType[0] == PARTICLE_TYPE_LAUNCHER)  UpdateLauncher();
    else if (gType[0] == PARTICLE_TYPE_SHELL)  UpdateShell();
    else if (gType[0] == PARTICLE_TYPE_SEC_SHELL)  UpdateSecShell();
}
