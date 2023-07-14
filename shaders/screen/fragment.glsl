#version 330 core

in vec2 fTexCoord;   //纹理坐标

out vec4 color;

uniform sampler2D fScreen;   //屏幕纹理

const float offset = 1.0 / 300.0;
const float[] kSharpen = float[](-1, -1, -1, -1,  9, -1, -1, -1, -1); //锐化
const float[] kBlur = float[](1.0/16, 2.0/16, 1.0/16, 2.0/16, 4.0/16, 2.0/16, 1.0/16, 2.0/16, 1.0/16); //模糊
const float[] kEdge = float[](1, 1, 1, 1, -8, 1, 1, 1, 1); //边缘检测

vec4 Inversion(vec4 color) {//反相
    return vec4(vec3(1.0 - color), 1.0);
}

vec4 Grey(vec4 color) {//灰度
    float mean = dot(vec3(0.2126, 0.7152, 0.0722), color.rgb);
    return vec4(vec3(mean), 1.0);
}

vec4 Convolution(float[9] kernal) {//卷积
    vec3 color = vec3(0.0);
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            int pos = i * 3 + j;
            color += kernal[pos] * vec3(texture(fScreen, fTexCoord.st + offset * vec2(i - 1, j - 1)));
        }
    }
    return vec4(color, 1.0);
}

vec4 ReinhardMapping(vec4 color) {
    vec3 hdr = color.rgb;
    vec3 reinhard = hdr / (hdr + vec3(1.0f));
    return vec4(reinhard, 1.0f);
}

vec4 ExpMapping(vec4 color, float exposure) {
    vec3 hdr = color.rgb;
    vec3 tone = vec3(1.0f) - exp(-hdr * exposure);
    return vec4(tone, 1.0f);
}

vec4 ACESToneMapping(vec4 color) {
    const float A = 2.51f;
    const float B = 0.03f;
    const float C = 2.43f;
    const float D = 0.59f;
    const float E = 0.14f;

    vec3 hdr = color.rgb;
    vec3 tone = (hdr * (A * hdr + B)) / (hdr * (C * hdr + D) + E);

    return vec4(tone, 1.0);
}

void main() {
    color = texture(fScreen, fTexCoord);
    //color = Grey(color);
    //color = Convolution(kEdge);
    color = ExpMapping(color, 1.0f);
    //color = ReinhardMapping(color);
}
