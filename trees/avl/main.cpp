#include "avl.hpp"
#include <random>
#include <ctime>

using namespace std;

inline void printVec(const vector<int>& vec) {
    for (uint32_t i = 0; i < vec.size(); ++i) {
        if (i) cout << " ";
        cout << vec[i];
    }
    cout << endl;
}

int main() {
    srand(time(nullptr));
    AVLTree<int> avl;
    //avl.insert(10);
    //avl.insert(20);
    //avl.insert(15);
    //avl.traverseNodes();
    AVLTree<int> tree2({11,32,95,89,66,73,90,40,99,72,28,61,29,82,68,7,33,6,57,47});
    printVec(tree2.getPreOrder());
    cout << tree2.size() << endl;
    return 0;
    std::string input("");
    vector<int> vec({11,32,95,89,66,73,90,40,99,72,28,61,29,82,68,7,33,6,57,47});
    int arr[] = {1, 2, 3, 5};
    std::cout << (sizeof(arr) / sizeof(int)) << std::endl;
    vec.clear();
    for (int i = 0; i < 50; ++i) {
        int random = rand() % 300;
        vec.push_back(random);
    }

    for (int i = 0; i < vec.size(); ++i) {
        input += std::to_string(vec[i]) + ",";
        avl.insert(vec[i]);
    }
    std::cout << input << std::endl;
    //avl.insert(20);
    //avl.insert(10);
    //avl.insert(15);
    //avl.insert(13);
    //avl.insert(17);
    //avl.insert(19);
    //avl.traverseNodes();
    //avl.insert(5);
    //avl.insert(3);
    //avl.insert(1);
    //avl.insert(3);
    //avl.insert(5);
    //avl.insert(4);
    //avl.insert(1);
    //avl.insert(2);
    //avl.insert(3);
    //avl.insert(5);
    //avl.insert(7);
    //avl.insert(10);
    //avl.insert(8);
    //avl.traverseNodes();
    cout << "PreOrder\n";
    vector<int> preorder = avl.getPreOrder();
    printVec(preorder);
    cout << "InOrder\n";
    vector<int> inorder = avl.getInOrder();
    printVec(inorder);
    return 0;
}
