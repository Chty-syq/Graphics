#version 330 core

#define PARTICLE_TYPE_LAUNCHER 0.0f
#define PARTICLE_TYPE_SHELL 1.0f

layout (points) in;
layout (points, max_vertices = 10) out;

in vec3 gPosition[];
in vec3 gVelocity[];
in float gAlpha[];
in float gType[];
in float gSize[];
in float gLifetime[];
in float gLifespan[];   //寿命

out vec3 fPosition;
out vec3 fVelocity;
out float fAlpha;
out float fType;
out float fSize;
out float fLifetime;
out float fLifespan;

uniform float gDeltaTime;
uniform float gTime;
uniform float gRadius;  //火焰半径
uniform float gLifespanMax;
uniform float gLifespanMin;
uniform vec3 gVelocityMax;
uniform vec3 gVelocityMin;

uniform sampler1D gRandomMap;

float age = gLifetime[0] + gDeltaTime;

vec3 GetRandomFloats(float texCoord) {  //random number from [0, 1]
    vec3 number = texture(gRandomMap, texCoord).xyz;
    return number;
}

void UpdateLauncher() {
    float lifespan = gLifespan[0];
    if (age >= gLifespan[0]) { //发射shell并重置launcher
        vec3 random = GetRandomFloats(gLifespan[0]);
        fPosition = gPosition[0];
        fVelocity = (gVelocityMax - gVelocityMin) * random.x + gVelocityMin;
        fAlpha = gAlpha[0];
        fType = PARTICLE_TYPE_SHELL;
        fSize = gSize[0];
        fLifetime = 0.0f;
        fLifespan = (gLifespanMax - gLifespanMin) * random.y + gLifespanMin;
        EmitVertex();
        EndPrimitive();

        age = 0.0f;
        lifespan = (gLifespanMax - gLifespanMin) * random.z + gLifespanMin;
    }
    fPosition = gPosition[0];
    fVelocity = gVelocity[0];
    fAlpha = gAlpha[0];
    fType = PARTICLE_TYPE_LAUNCHER;
    fSize = gSize[0];
    fLifetime = age;
    fLifespan = lifespan;
    EmitVertex();
    EndPrimitive();
}

void UpdateShell() {
    if (age < gLifespan[0]) {
        fPosition = gPosition[0] + gDeltaTime * gVelocity[0];
        fVelocity = gVelocity[0] + gDeltaTime * vec3(0.0f, 0.1f, 0.0f);
        fType = PARTICLE_TYPE_SHELL;
        fLifetime = age;
        fLifespan = gLifespan[0];
        float factor = 1.0f / ((age - 0.5f * gLifespan[0]) * (age - 0.5f * gLifespan[0]) + 1.0f);
        fAlpha = factor;
        fSize = factor * 0.05f;
        EmitVertex();
        EndPrimitive();
    }
}

void main() {
    if (gType[0] == PARTICLE_TYPE_LAUNCHER)  UpdateLauncher();
    else if (gType[0] == PARTICLE_TYPE_SHELL)  UpdateShell();
}
