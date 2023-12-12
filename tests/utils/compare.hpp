#ifndef __COMPARE_UTILS_H__
#define __COMPARE_UTILS_H__

#include <cstdint>
#include <iostream>
#include <vector>

namespace utils
{

template <typename T>
bool vecAreSame(const std::vector<T> &expected, const std::vector<T> &actual)
{
    if (expected.size() != actual.size()) {
        std::cerr << "Vectors => size mismatch\n";
        std::cerr << "Vectors => expected size: " << expected.size()
                  << ", actual: " << actual.size() << std::endl;
        return false;
    }

    bool areSame = true;
    uint32_t i = 0;
    for (; i < expected.size(); ++i) {
        if (expected[i] != actual[i]) {
            areSame = false;
            break;
        }
    }

    if (!areSame) {
        std::cerr << "Failed assert at index [" << i << "]" << std::endl;
        std::cerr << "Expected => " << expected[i] << " <> actual: " << actual[i] << std::endl;
    }
    return areSame;
}

template <typename T>
bool vec2dAreSame(const std::vector<std::vector<T>> &expected,
                    const std::vector<std::vector<T>> &actual)
{
    if (expected.size() != actual.size()) {
        std::cerr << "Vectors => size mismatch\n";
        std::cerr << "Vectors => expected size: " << expected.size()
                  << ", actual: " << actual.size() << std::endl;
        return false;
    }

    bool areSame = true;
    uint32_t i = 0, j = 0;
    for (; i < expected.size(); ++i) {
        if (expected[i].size() != actual[i].size()) {
            std::cerr << "Vectors => size mismatch at [" << i << "," << j << "]" << std::endl;
            std::cerr << "Vectors => expected size: " << expected[i][j].size()
                      << ", actual: " << actual[i][j] << std::endl;
            return false;
        }

        for (; j < expected[i].size(); ++i) {
            if (expected[i][j] != actual[i][j]) {
                areSame = false;
                break;
            }
        }
    }

    if (!areSame) {
        std::cerr << "Failed assert at index [" << i << "," << j << "]" << std::endl;
        std::cerr << "Expected: " << expected[i][j] << " <> actual: " << actual[i][j] << std::endl;
    }

    return areSame;
}

};
#endif
