#include <algorithm>
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include "bst.hpp"

using ::testing::ElementsAre;

TEST(BSTTest, Test1)
{
    BST<int> tree;
    vector<int> vec({8, 9, 6, 7, 6, 6, 4, 5});
    for (auto &item : vec) tree.insert(item);
    sort(vec.begin(), vec.end());
    auto i1 = tree.getInOrder();
    ASSERT_THAT(i1, vec);

    auto v1 = tree.getPreOrder();
    ASSERT_THAT(v1, ElementsAre(8, 6, 6, 6, 4, 5, 7, 9));

    tree.erase(9);
    tree.erase(8);
    tree.erase(6);
    v1 = tree.getPreOrder();
    ASSERT_THAT(v1, ElementsAre(7, 4, 5));
}

TEST(BSTTest, Test2)
{
    BST<int> tree;
    vector<int> vec({10, 11, 4, 7, 8, 9, 6, 5, 6, 2, 1, 3, 4, 4});
    for (auto &item : vec) tree.insert(item);
    auto v1 = tree.getPreOrder();
    ASSERT_THAT(v1, ElementsAre(10, 4, 4, 4, 2, 1, 3, 7, 6, 6, 5, 8, 9, 11));

    sort(vec.begin(), vec.end());
    auto v2 = tree.getInOrder();
    ASSERT_THAT(v2, vec);
}
