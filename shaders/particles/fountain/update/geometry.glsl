#version 330 core

#define PARTICLE_TYPE_LAUNCHER 0.0f
#define PARTICLE_TYPE_SHELL 1.0f
#define PARTICLE_TYPE_SEC_SHELL 2.0f

layout (points) in;
layout (points, max_vertices = 10) out;

in vec3 gPosition[];
in vec3 gVelocity[];
in float gType[];
in float gLifetime[];

out vec3 fPosition;
out vec3 fVelocity;
out float fType;
out float fLifetime;

uniform float gRadius;
uniform float gTheta;
uniform vec3 gNormal;
uniform float gDeltaTime;
uniform float gTime;
uniform float gLifespanMax;
uniform float gLifespanMin;

uniform sampler1D gRandomMap;

const float PI = acos(-1.0f);

float age = gLifetime[0] - gDeltaTime;

vec3 GetRandomFloats(float texCoord) {  //random number from [0, 1]
    vec3 number = texture(gRandomMap, texCoord).xyz;
    return number;
}

void UpdateLauncher() {
    if (age <= 0) { //发射shell并重置launcher
        vec3 random = GetRandomFloats(gLifetime[0]);
        float theta = random.x * (gTheta / 2);
        float phi = random.y * (2 * PI);
        float dist = length(gPosition[0]);
        fVelocity = vec3(sin(theta) * cos(phi), 0.0f, sin(theta) * sin(phi));
        fVelocity = normalize(fVelocity) * 5.0f;
        fVelocity.y = 12.0f + 2.0f * (1 - pow(dist / gRadius, 2));

        fPosition = gPosition[0];
        fType = PARTICLE_TYPE_SHELL;
        fLifetime = gLifetime[0];
        EmitVertex();
        EndPrimitive();

        age = (gLifespanMax - gLifespanMin) * random.z + gLifespanMin;
    }
    fPosition = gPosition[0];
    fVelocity = gVelocity[0];
    fType = PARTICLE_TYPE_LAUNCHER;
    fLifetime = age;
    EmitVertex();
    EndPrimitive();
}

void UpdateShell() {
    if (gPosition[0].y >= 0) {
        fPosition = gPosition[0] + gDeltaTime * gVelocity[0];
        fVelocity = gVelocity[0] + gDeltaTime * vec3(0.0f, -9.81f, 0.0f);
        fType = PARTICLE_TYPE_SHELL;
        fLifetime = age;
        EmitVertex();
        EndPrimitive();
    } else { //落到地面
        fPosition = vec3(gPosition[0].x, 0.0f, gPosition[0].z);
        fVelocity = (gVelocity[0] - 2 * dot(gVelocity[0], gNormal) * gNormal) * 0.2;
        fType = PARTICLE_TYPE_SEC_SHELL;
        fLifetime = age;
        EmitVertex();
        EndPrimitive();
    }
}

void UpdateSecShell() {
    if (gPosition[0].y >= 0) {
        fPosition = gPosition[0] + gDeltaTime * gVelocity[0];
        fVelocity = gVelocity[0] + gDeltaTime * vec3(0.0f, -9.81f, 0.0f);
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
