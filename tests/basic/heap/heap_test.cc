#include <algorithm>
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include "heap.hpp"

std::vector<int> cppHeap(std::vector<int>& input)
{
    std::vector<int> output;
    for (auto &item : input)
    {
        output.push_back(item);
        std::make_heap(output.begin(), output.end());
    }
    return output;
}

TEST(HeapTest, Test_1)
{
    Heap<int> heap;
    vector<int> input({93,67,51,74,9,8,14,50,92,62,91,58,5,20,68,55,23,18,29,13,94,27,98,73,84,96,29,22,7,25,95,0,93,98,74,2,6,40,5,51,2,96,9,7,69,30,14,92,0,43,57,94,70,56,19,6,52,0,81,11,26,28,63,19,26,37,73,33,29,30,84,31,79,45,90,48,27,56,40,28,51,49,74,73,5,46,80,10,46,61,21,72,89,85,43,15,74,17,0,4});

    vector<int> res = cppHeap(input);
    for (auto &item : input) heap.insert(item);

    while (!heap.empty()) {
        std::pop_heap(res.begin(), res.end());
        res.pop_back();
        heap.pop();
        ASSERT_THAT(res, vector<int>(heap.begin(), heap.end()));
    }
}
