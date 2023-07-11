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

void main() {
    color = texture(fScreen, fTexCoord);
    //color = Grey(color);
    //color = Convolution(kEdge);
}
