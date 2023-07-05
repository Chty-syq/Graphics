#version 330 core

in vec2 fTexCoord;   //纹理坐标
in vec3 fNormal;     //法向量
in vec3 fPosition;   //片元位置(世界系)

out vec4 color;

uniform sampler2D fTexture;  //纹理

uniform vec3 fLightPos;     //光源位置
uniform vec3 fLightColor;   //光颜色
uniform vec3 fViewPos;      //视点位置

void main() {
    vec3 norm = normalize(fNormal);                     //法线
    vec3 lightDir = normalize(fLightPos - fPosition);   //入射光方向
    vec3 reflectDir = reflect(-lightDir, norm);         //反射光方向
    vec3 viewDir = normalize(fViewPos - fPosition);     //视角方向

    float ambient = 0.1;                                           //环境光
    float diffuse = max(dot(norm, lightDir), 0.0);                 //漫反射
    float specular = pow(max(dot(viewDir, reflectDir), 0.0), 32);  //镜面反射

    vec3 light = (ambient + diffuse + specular) * fLightColor;
    color = vec4(light * texture(fTexture, fTexCoord).rgb, 1.0);
}
