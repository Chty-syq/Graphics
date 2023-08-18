//
// Created by syq on 23-8-17.
//

#pragma once
#include "common/defs.hpp"

namespace Grammar {
    std::map<char, vector<std::string>> generations;

    std::string Search(char target);
    void Clear();
    void AddGeneration(char target, const std::string& ref);
    std::string Iteration(const std::string& start, int level);
};

void Grammar::AddGeneration(char target, const std::string& ref) {
    if (generations.contains(target)) {
        generations[target].push_back(ref);
    } else {
        generations[target] = { ref };
    }
}

void Grammar::Clear() {
    generations.clear();
}

std::string Grammar::Iteration(const std::string& start, int level) {
    std::string result = start;
    for(int i = 0; i < level; ++i) {
        std::string str;
        for(const auto& ch : result) {
            str += Search(ch);
        }
        result = str;
    }
    return result;
}

std::string Grammar::Search(char target) {
    if (!generations.contains(target)) { //沒有产生式，则返回自身
        return { target };
    }
    vector<std::string> generation;
    std::sample(generations[target].begin(), generations[target].end(), std::back_inserter(generation), 1, utils::generator());
    return generation[0];
}
