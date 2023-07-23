#include "bst.hpp"

void printVec(vector<int> vec)
{
    for (int &item : vec) cout << item << " ";
    cout << endl;
}

int main()
{
    BST<int> tree;
    tree.insert(8);
    tree.insert(9);
    tree.insert(6);
    tree.insert(7);
    tree.insert(6);
    tree.insert(6);
    tree.insert(4);
    tree.insert(5);
    auto v1 = tree.getPreOrder();
    printVec(tree.getInOrder());
    printVec(v1);

    cout << "\nDeleting 8" << endl;
    tree.erase(8);
    auto v2 = tree.getPreOrder();
    printVec(v2);

    cout << "\nDeleting 9" << endl;
    tree.erase(9);
    auto v3 = tree.getPreOrder();
    printVec(v3);

    cout << "\nDeleting 6" << endl;
    tree.erase(6);
    auto v4 = tree.getPreOrder();
    printVec(v4);

    BST<int> t2;
    vector<int> vec({10, 11, 4, 7, 8, 9, 6, 5, 6, 2, 1, 3, 4, 4});
    for (int &item : vec) t2.insert(item);
    printVec(t2.getInOrder());
    printVec(t2.getPreOrder());
    return 0;
}
