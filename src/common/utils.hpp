//
// Created by syq on 23-7-4.
//
#pragma once
#include <iostream>
#include <random>
#include <cmath>

namespace utils {
    inline std::mt19937& generator() {
        static thread_local std::mt19937 gen(std::random_device{}());
        return gen;
    }

    int RandomInt(int s, int t) {
        std::uniform_int_distribution<int> dist(s, t);
        return dist(generator());
    }

    float RandomFloat(float s, float t) {
        std::uniform_real_distribution<float> dist(s, t);
        return dist(generator());
    }
}