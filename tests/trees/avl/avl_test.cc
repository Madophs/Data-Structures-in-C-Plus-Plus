#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "avl.hpp"
#include "../../utils/compare.hpp"

using ::testing::ElementsAre;
TEST(AVLTest, Test1)
{
    AVLTree<int> avl({11,32,95,89,66,73,90,40,99,72,28,61,29,82,68,7,33,6,57,47});
    auto preorder = avl.getPreOrder();
    auto inorder = avl.getInOrder();
    auto postorder = avl.getPostOrder();
    ASSERT_THAT(inorder, ElementsAre(6, 7, 11, 28, 29, 32, 33, 40, 47, 57, 61, 66, 68, 72, 73, 82, 89, 90, 95, 99));
    ASSERT_THAT(preorder, ElementsAre(66, 32, 28, 7, 6, 11, 29, 40, 33, 57, 47, 61, 89, 73, 72, 68, 82, 95, 90, 99));
    ASSERT_THAT(postorder, ElementsAre(6, 11, 7, 29, 28, 33, 47, 61, 57, 40, 32, 68, 72, 82, 73, 90, 99, 95, 89, 66));
    ASSERT_EQ(avl.size(), 20);
    ASSERT_EQ(preorder.size(), 20);
    ASSERT_TRUE(avl.exists(89));
    ASSERT_FALSE(avl.exists(91));
}

TEST(AVLTest, Test2)
{
    AVLTree<int> avl({264,294,26,113,56,161,67,231,16,6,124,112,231,7,237,249,192,298,275,145,0,198,131,89,76,115,78,142,29,244,186,45,291,265,210,99,178,277,31,246,35,207,59,267,215,296,216,159,46,243,5,47,141,188,188,217,3,266,59,84,263,297,129,254,262,40,53,141,69,136,139,105,96,198,124,11,246,92,170,293,35,227,92,228,115,32,197,170,299,8,254,262,5,136,268,268,228,73,161,297,262,0,154,58,251,278,121,197,70,291,242,157,271,34,137,138,67,34,9,118,42,263,132,48,151,152,68,79,225,281,129,187,33,283,297,284,262,118,234,84,110,176,294,133,263,131,271,82,166,32,252,260,48,84,60,199,236,128,31,213,161,160,101,195,143,98,179,157,217,113,242,79,42,288,264,5,119,235,87,37,20,39,298,68,175,110,267,163,291,298,76,152,158,177,47,54,28,279,211,297,144,205,128,186,193,92,243,65,79,30,102,99,121,152,167,48,263,187,211,254,237,288,158,96,217,258,202,297,237,113,294,81,71,174,20,264,18,263,81,98,46,236,249,219,88,169,268,103,56,231,109,293,219,20,141,189,278,43,186,215,209,233,48,32,107,120,296,126,84,130,276,182,66,277,101,206,146,121,62,202,53,171,248,24,243,141,213,221,237,152,136,146,85,237,178,244,57,226,122,193,108,98,127,174,76,229,81,274,102,195,177,207,118,177,232,62,18,197,283,255,49,172,153,186,161,83,131,218,62,253,164,170,104,291,97,232,272,230,206,127,125,135,34,243,12,18,5,83,216,289,90,17,213,296,204,74,79,87,44,193,92,208,64,248,252,161,180,224,91,87,51,268,274,138,211,39,156,217,122,72,258,212,142,171,208,46,297,40,185,41,233,277,250,49,278,254,262,158,178,105,297,282,73,272,120,285,11,276,254,185,101,264,149,243,187,110,41,184,150,278,225,135,255,227,185,285,181,147,144,112,253,193,94,26,165,266,63,228,242,17,113,95,33,15,38,220,125,131,104,27,109,82,162,117,9,99,102,243,247,246,55,252,140,201,30,57,167,94,38,161,163,203,257,197,218,295,169,43,179,274,70,288,56,285,105,117,84,208,60,31,206,115,35,98,16,66,208,235,212,246});
    auto preorder = avl.getPreOrder();
    auto inorder = avl.getInOrder();
    auto postorder = avl.getPostOrder();
    ASSERT_TRUE(utils::vecAreSame(preorder, std::vector<int>({161, 56, 35, 16, 6, 3, 0, 5, 11, 8, 7, 9, 12, 15, 29, 20, 18, 17, 26, 24, 28, 27, 32, 31, 30, 34, 33, 46, 42, 39, 37, 38, 40, 41, 44, 43, 45, 49, 48, 47, 53, 51, 54, 55, 113, 89, 70, 65, 60, 58, 57, 59, 63, 62, 64, 67, 66, 69, 68, 79, 73, 71, 72, 76, 74, 78, 84, 82, 81, 83, 87, 85, 88, 99, 96, 91, 90, 94, 92, 95, 98, 97, 105, 102, 101, 103, 104, 110, 108, 107, 109, 112, 141, 131, 124, 120, 118, 115, 117, 119, 121, 122, 128, 126, 125, 127, 129, 130, 137, 133, 132, 136, 135, 139, 138, 140, 154, 149, 145, 143, 142, 144, 146, 147, 151, 150, 152, 153, 159, 157, 156, 158, 160, 231, 192, 176, 170, 166, 164, 163, 162, 165, 167, 169, 174, 171, 172, 175, 184, 180, 178, 177, 179, 182, 181, 186, 185, 188, 187, 189, 207, 202, 198, 195, 193, 197, 199, 201, 205, 204, 203, 206, 215, 211, 209, 208, 210, 213, 212, 225, 219, 217, 216, 218, 221, 220, 224, 227, 226, 229, 228, 230, 264, 244, 236, 234, 233, 232, 235, 242, 237, 243, 254, 249, 247, 246, 248, 252, 251, 250, 253, 258, 255, 257, 262, 260, 263, 283, 275, 267, 266, 265, 271, 268, 274, 272, 278, 277, 276, 281, 279, 282, 291, 288, 284, 285, 289, 296, 294, 293, 295, 298, 297, 299})));

    ASSERT_TRUE(utils::vecAreSame(inorder, std::vector<int>({0, 3, 5, 6, 7, 8, 9, 11, 12, 15, 16, 17, 18, 20, 24, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 51, 53, 54, 55, 56, 57, 58, 59, 60, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 76, 78, 79, 81, 82, 83, 84, 85, 87, 88, 89, 90, 91, 92, 94, 95, 96, 97, 98, 99, 101, 102, 103, 104, 105, 107, 108, 109, 110, 112, 113, 115, 117, 118, 119, 120, 121, 122, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 149, 150, 151, 152, 153, 154, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 169, 170, 171, 172, 174, 175, 176, 177, 178, 179, 180, 181, 182, 184, 185, 186, 187, 188, 189, 192, 193, 195, 197, 198, 199, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 215, 216, 217, 218, 219, 220, 221, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 242, 243, 244, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 257, 258, 260, 262, 263, 264, 265, 266, 267, 268, 271, 272, 274, 275, 276, 277, 278, 279, 281, 282, 283, 284, 285, 288, 289, 291, 293, 294, 295, 296, 297, 298, 299})));

    ASSERT_TRUE(utils::vecAreSame(postorder, std::vector<int>({0, 5, 3, 7, 9, 8, 15, 12, 11, 6, 17, 18, 24, 27, 28, 26, 20, 30, 31, 33, 34, 32, 29, 16, 38, 37, 41, 40, 39, 43, 45, 44, 42, 47, 48, 51, 55, 54, 53, 49, 46, 35, 57, 59, 58, 62, 64, 63, 60, 66, 68, 69, 67, 65, 72, 71, 74, 78, 76, 73, 81, 83, 82, 85, 88, 87, 84, 79, 70, 90, 92, 95, 94, 91, 97, 98, 96, 101, 104, 103, 102, 107, 109, 108, 112, 110, 105, 99, 89, 117, 115, 119, 118, 122, 121, 120, 125, 127, 126, 130, 129, 128, 124, 132, 135, 136, 133, 138, 140, 139, 137, 131, 142, 144, 143, 147, 146, 145, 150, 153, 152, 151, 149, 156, 158, 157, 160, 159, 154, 141, 113, 56, 162, 163, 165, 164, 169, 167, 166, 172, 171, 175, 174, 170, 177, 179, 178, 181, 182, 180, 185, 187, 189, 188, 186, 184, 176, 193, 197, 195, 201, 199, 198, 203, 204, 206, 205, 202, 208, 210, 209, 212, 213, 211, 216, 218, 217, 220, 224, 221, 219, 226, 228, 230, 229, 227, 225, 215, 207, 192, 232, 233, 235, 234, 237, 243, 242, 236, 246, 248, 247, 250, 251, 253, 252, 249, 257, 255, 260, 263, 262, 258, 254, 244, 265, 266, 268, 272, 274, 271, 267, 276, 277, 279, 282, 281, 278, 275, 285, 284, 289, 288, 293, 295, 294, 297, 299, 298, 296, 291, 283, 264, 231, 161})));
    ASSERT_EQ(avl.size(), 244);
    ASSERT_EQ(preorder.size(), 244);
}

TEST(AVLTest, Deletion1)
{
    AVLTree<int> avl({83, 25, 63, 42, 38, 60, 99, 46, 79, 54});
    std::vector<int> removalOrder({25, 38, 42, 46, 54, 60, 63, 79, 83, 99});
    std::vector<std::vector<int>> preorderExpected(
            {
                {63, 42, 38, 54, 46, 60, 83, 79, 99},
                {63, 54, 42, 46, 60, 83, 79, 99},
                {63, 54, 46, 60, 83, 79, 99},
                {63, 54, 60, 83, 79, 99},
                {63, 60, 83, 79, 99},
                {83, 63, 79, 99},
                {83, 79, 99},
                {83, 99},
                {99},
                {}
            });

    for (auto i = 0u; i < removalOrder.size(); ++i) {
        avl.remove(removalOrder[i]);
        auto preorderActual = avl.getPreOrder();
        ASSERT_TRUE(utils::vecAreSame(preorderExpected[i], preorderActual));
    }

    ASSERT_EQ(avl.size(), 0);
}

TEST(AVLTest, Deletion2)
{
    AVLTree<int> avl({6, 4, 53, 81, 48, 24, 23, 93, 34, 3, 29, 14, 33, 26, 72, 28, 30, 64, 88, 89});
    std::vector<int> removalOrder({89, 88, 30, 28, 26, 72, 14, 3, 29, 48, 53, 24, 81, 23, 64, 6, 93, 34, 4, 33});
    std::vector<std::vector<int>> preorderExpected(
        {
            {24, 6, 4, 3, 23, 14, 48, 29, 28, 26, 33, 30, 34, 81, 64, 53, 72, 93, 88 },
            {24, 6, 4, 3, 23, 14, 48, 29, 28, 26, 33, 30, 34, 81, 64, 53, 72, 93 },
            {24, 6, 4, 3, 23, 14, 48, 29, 28, 26, 33, 34, 81, 64, 53, 72, 93 },
            {24, 6, 4, 3, 23, 14, 48, 29, 26, 33, 34, 81, 64, 53, 72, 93 },
            {24, 6, 4, 3, 23, 14, 48, 33, 29, 34, 81, 64, 53, 72, 93 },
            {24, 6, 4, 3, 23, 14, 48, 33, 29, 34, 81, 64, 53, 93 },
            {24, 6, 4, 3, 23, 48, 33, 29, 34, 81, 64, 53, 93 },
            {48, 24, 6, 4, 23, 33, 29, 34, 81, 64, 53, 93 },
            {48, 24, 6, 4, 23, 33, 34, 81, 64, 53, 93 },
            {53, 24, 6, 4, 23, 33, 34, 81, 64, 93 },
            {64, 24, 6, 4, 23, 33, 34, 81, 93 },
            {64, 33, 6, 4, 23, 34, 81, 93 },
            {33, 6, 4, 23, 64, 34, 93 },
            {33, 6, 4, 64, 34, 93 },
            {33, 6, 4, 93, 34 },
            {33, 4, 93, 34 },
            {33, 4, 34 },
            {33, 4 },
            {33 },
            {},
        });
    for (auto i = 0u; i < removalOrder.size(); ++i) {
        avl.remove(removalOrder[i]);
        auto preorderActual = avl.getPreOrder();
        ASSERT_TRUE(utils::vecAreSame(preorderExpected[i], preorderActual));
    }

    ASSERT_EQ(avl.size(), 0);
}