#include <cstdlib>
#include <functional>
#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <set>
#include "heap.hpp"

template <typename InputIterator>
void print(InputIterator i_begin, InputIterator i_end)
{
    for (InputIterator iter = i_begin; iter != i_end; iter++) {
        std::cout << *(iter) << ",";
    }
}

std::vector<int> stepWiseInsertion(std::vector<int>& input)
{
    std::vector<int> output;
    for (auto &item : input)
    {
        output.push_back(item);
        std::make_heap(output.begin(), output.end());
    }
    return output;
}

bool custom(const int& a, const int& b)
{
    return a > b;
}

int main()
{
    srand(time(0));
    std::vector<int> vec;
    for (int i = 0; i < 100; ++i) {
        int random = rand() % 100;
        vec.push_back(random);
    }

    std::vector<int> res = stepWiseInsertion(vec);
    std::cout << "C++ Heap" << std::endl;
    print(res.begin(), res.end());
    std::cout << std::endl;

    Heap<int> heap(custom);
    for (auto &item : vec) heap.insert(item);
    std::cout << "My Heap :)\n" << std::endl;
    print(heap.begin(), heap.end());
    std::cout << std::endl;

    while (!heap.empty()) {
        std::pop_heap(res.begin(), res.end());
        res.pop_back();
        heap.pop();
        std::cout << "\nC++ Heap\n";
        print(res.begin(), res.end());
        cout << "\nMy Heap\n";
        print(heap.begin(), heap.end());
        std::cout << std::endl;
    }

    return 0;
}
