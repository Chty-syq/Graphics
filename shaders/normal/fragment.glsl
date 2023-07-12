#version 330 core

#define NUM_POINT_LIGHT 4

in vec2 fTexCoord;      //纹理坐标
in vec3 fNormal;        //法向量
in vec3 fPosition;      //片元位置(世界系)
in vec4 fPositionLight; //片元位置(光源坐标系)

out vec4 color;

struct Material {               //材质
    sampler2D mDiffuse;
    sampler2D mSpecular;
    float mShininess;
};
struct LightFactor {            //光照因子
    vec3 fAmbient;
    vec3 fDiffuse;
    vec3 fSpecular;
};
struct LightParal {             //平行光
    vec3        pDirection;     //方向
    LightFactor pFactor;
};
struct LightPoint {             //点光源
    vec3        pPosition;      //位置
    vec3        pCoefficient;   //衰减系数
    LightFactor pFactor;
};
struct LightSpot {              //聚光
    vec3        sDirection;     //聚光方向
    float       sCutoffInner;   //内切光角
    float       sCutoffOuter;   //外切光角
    LightPoint  sLightPoint;    //点光源
};

uniform bool blinn;             //是否启用blinn-phong光照模型
uniform sampler2D fShadowMap;   //阴影贴图

uniform vec3 fViewPos;                              //视点位置
uniform Material material;                          //物体材质
uniform LightParal fLightParal;                     //平行光
uniform LightPoint fLightPoint[NUM_POINT_LIGHT];    //点光源
uniform LightSpot fLightSpot;                       //聚光

float GetDiffuseStrength(vec3 lightDir, vec3 norm) {
    return max(dot(norm, lightDir), 0.0);
}

float GetSpecularStrength(vec3 lightDir, vec3 norm) {
    vec3 viewDir = normalize(fViewPos - fPosition);     //视角方向
    if (!blinn) {
        vec3 reflectDir = reflect(-lightDir, norm);         //反射光方向
        return pow(max(dot(viewDir, reflectDir), 0.0), material.mShininess);
    }
    else {
        vec3 halfDir = normalize(lightDir + viewDir);   //半程向量
        return pow(max(dot(halfDir, norm), 0.0), material.mShininess);
    }
}

float GetLightParalShadow(vec3 lightDir, vec3 norm) {
    vec3 proj_coords = fPositionLight.xyz / fPositionLight.w;
    if (proj_coords.z > 1.0) return 0.0;
    proj_coords = proj_coords * 0.5 + 0.5;

    float current_depth = proj_coords.z;
    float bias = max(0.005, 0.05 * (1.0 - dot(lightDir, norm)));

    float shadow = 0.0;
    vec2 stride = 1.0 / textureSize(fShadowMap, 0);
    for(int i = -1; i <= 1; ++i) {
        for(int j = -1; j <= 1; ++j) {
            float closest_depth = texture(fShadowMap, proj_coords.xy + vec2(i, j) * stride).r;
            shadow += current_depth - bias > closest_depth ? 1.0 : 0.0;
        }
    }
    return shadow / 9.0;
}

vec3 GetLightParal(LightParal light, vec3 norm) {
    vec3 lightDir = normalize(-light.pDirection);
    vec3 reflectDir = reflect(-lightDir, norm);

    float shadow = GetLightParalShadow(lightDir, norm);
    float diffuse = GetDiffuseStrength(lightDir, norm) * (1 - shadow);
    float specular = GetSpecularStrength(lightDir, norm) * (1 - shadow);

    vec3 diffuseTex = texture(material.mDiffuse, fTexCoord).rgb * (light.pFactor.fDiffuse * diffuse + light.pFactor.fAmbient);
    vec3 specularTex = texture(material.mSpecular, fTexCoord).rgb * (light.pFactor.fSpecular * specular);
    return (diffuseTex + specularTex);
}

vec3 GetLightPoint(LightPoint light, vec3 norm) {
    vec3 lightDir = normalize(light.pPosition - fPosition);

    float diffuse = GetDiffuseStrength(lightDir, norm);
    float specular = GetSpecularStrength(lightDir, norm);

    float distance = length(light.pPosition - fPosition);
    float attenuation = 1.0 / dot(light.pCoefficient, vec3(1.0, distance, pow(distance, 2)));  //衰减因子

    vec3 diffuseTex = texture(material.mDiffuse, fTexCoord).rgb * (light.pFactor.fDiffuse * diffuse + light.pFactor.fAmbient);
    vec3 specularTex = texture(material.mSpecular, fTexCoord).rgb * (light.pFactor.fSpecular * specular);
    return attenuation * (diffuseTex + specularTex);
}

vec3 GetLightSpot(LightSpot light, vec3 norm) {
    vec3 lightDir = normalize(light.sLightPoint.pPosition - fPosition);

    float theta = dot(lightDir, -normalize(light.sDirection));
    float intensity = clamp((theta - light.sCutoffOuter) / (light.sCutoffInner - light.sCutoffOuter), 0.0, 1.0);

    return intensity * GetLightPoint(light.sLightPoint, norm);
}

void main() {
    vec3 norm = normalize(fNormal);                     //法线
    vec3 viewDir = normalize(fViewPos - fPosition);     //视角方向

    vec3 light = vec3(0.0);
    light += GetLightParal(fLightParal, norm);
    light += GetLightSpot(fLightSpot, norm);
    for(int i = 0; i < NUM_POINT_LIGHT; ++i) {
        light += GetLightPoint(fLightPoint[i], norm);
    }
    color = vec4(light, 1.0);
}
