#include "avl.hpp"
#include <random>
#include <ctime>
#include <set>
#include <unordered_set>

using namespace std;

inline string vec2str(const vector<int>& vec) {
    string res = "";
    for (uint32_t i = 0; i < vec.size(); ++i) {
        if (i) res += ", ";
        res += to_string(vec[i]);
    }
    return res;
}

void randFill(vector<int>& vec, int randn) {
    srand(time(nullptr));
    vec.clear();
    vec.reserve(randn);

    set<int> uniq;
    for (int i = 0; i < randn;) {
        int randv = rand() % 100;
        if (uniq.find(randv) == uniq.end()) {
            uniq.insert(randv);
            vec.push_back(randv);
            ++i;
        }
    }
    cout << vec2str(vec) << endl;
}

void add2avl(AVLTree<int>& avl, const vector<int> &vec, unordered_set<int> &uniq) {
    for (auto val : vec) {
        uniq.insert(val);
        avl.insert(val);
    }
}

int main() {
    vector<int> vec({11,32,95,89,66,73,90,40,99,72,28,61,29,82,68,7,33,6,57,47});
    unordered_set<int> uniq;
    randFill(vec, 15);
    AVLTree<int> avl;
    std::cout << vec2str(vec) << endl;
    add2avl(avl, vec, uniq);

    vector<int> original(vec.begin(), vec.end());
    vector<int> removalOrder;
    vector<vector<int>> allExpected;
    for (auto val : uniq) {
        removalOrder.push_back(val);
        avl.remove(val);
        cout << "preorder: " << vec2str(avl.getPreOrder()) << endl;
        cout << "inorder: " << vec2str(avl.getInOrder()) << endl;
        allExpected.push_back(avl.getPreOrder());
    }

    for (auto i = 0u; i < allExpected.size(); ++i) {
        if (!i) {
            cout << "std::vector<std::vector<int>> preorderExpected(\n";
            cout << "{\n";
        }
        cout << "{" << vec2str(allExpected[i]) << "}" << " // " << removalOrder[i] << "\n";
        if (i + 1 == allExpected.size()) {
            cout << "});\n";
        }
    }

    cout << "Original " << vec2str(original) << endl;
    cout << "Removal " << vec2str(removalOrder) << endl;
    cout << "Unique elems: " << uniq.size() << endl;
    cout << "AVL size: " << avl.size() << endl;
    return 0;
}
