#ifndef __AVL_TREE__
#define __AVL_TREE__

#include <cstddef>
#include <initializer_list>
#include <ios>
#include <iostream>
#include <iterator>
#include <vector>
#include <stack>

template <class T>
class AVLTree
{
    struct AVLNode;
public:
    explicit AVLTree():m_size(0), m_root(nullptr)
    {
    }

    explicit AVLTree(std::initializer_list<T> nodes)
        :m_size(0), m_root(nullptr)
    {
        for  (const T& newNode : nodes) {
            insert(newNode);
        }
    }

    ~AVLTree() {
        deleteNodes();
    }

    std::size_t size() const {
        return m_size;
    }

    void insert(const T& value) {
        AVLNode* newNode = new AVLNode(value);
        if (m_root == nullptr) {
            m_root = newNode;
        } else {
            AVLNode* upfrontNode = m_root;
            AVLNode* prevNode = m_root;
            while (upfrontNode != nullptr) {
                prevNode = upfrontNode;
                if (newNode->value < upfrontNode->value) {
                    upfrontNode = upfrontNode->leftChild;
                } else if (newNode->value > upfrontNode->value) {
                    upfrontNode = upfrontNode->rightChild;
                } else {
                    break;
                }
            }

            if (newNode->value < prevNode->value) {
                prevNode->leftChild = newNode;
                newNode->parent = prevNode;
                ++m_size;
            } else if (newNode->value > prevNode->value) {
                prevNode->rightChild = newNode;
                newNode->parent = prevNode;
                ++m_size;
            } else {
                ++prevNode->count;
                delete newNode;
                newNode = nullptr;
                return;
            }

            AVLNode* traversalNode = newNode;
            while (traversalNode != nullptr && traversalNode->parent != nullptr) {
                AVLNode* parentNode = traversalNode->parent;
                parentNode->level = std::max(
                        parentNode->getLeftChildLevel() + 1,
                        parentNode->getRightChildLevel() + 1);
                int currentNodeDiff = traversalNode->getLeftChildLevel() - traversalNode->getRightChildLevel();
                int parentDiff = parentNode->getLeftChildLevel() - parentNode->getRightChildLevel();
                if (parentDiff == -2) {
                    if (currentNodeDiff == 1) {
                        rightRotation(traversalNode->leftChild);
                    } else {
                        leftRotation(traversalNode);
                    }
                } else if (parentDiff == 2) {
                    if (currentNodeDiff == -1) {
                        leftRotation(traversalNode->rightChild);
                    } else {
                        rightRotation(traversalNode);
                    }
                }
                traversalNode = traversalNode->parent;
            }
        }
    }

    void leftRotation(AVLNode* pivot) {
        AVLNode* parentNode = pivot->parent;
        pivot->parent = parentNode->parent;
        if (pivot->parent != nullptr) {
            if (pivot->value < pivot->parent->value) {
                pivot->parent->leftChild = pivot;
            } else {
                pivot->parent->rightChild = pivot;
            }
        }
        parentNode->rightChild = pivot->leftChild;
        if (parentNode->rightChild != nullptr) {
            parentNode->rightChild->parent = parentNode;
        }
        pivot->leftChild = parentNode;
        parentNode->parent = pivot;

        if (pivot->parent ==  nullptr) {
            m_root = pivot;
        }

        pivot->leftChild->level = std::max(
                pivot->leftChild->getLeftChildLevel() + 1,
                pivot->leftChild->getRightChildLevel() + 1);
        pivot->level = std::max(
                pivot->getLeftChildLevel() + 1,
                pivot->getRightChildLevel() + 1);
    }

    void rightRotation(AVLNode* pivot) {
        AVLNode* parentNode = pivot->parent;
        pivot->parent = parentNode->parent;

        if (pivot->parent != nullptr) {
            if (pivot->value < pivot->parent->value) {
                pivot->parent->leftChild = pivot;
            } else {
                pivot->parent->rightChild = pivot;
            }
        }
        parentNode->leftChild = pivot->rightChild;
        if (parentNode->leftChild != nullptr) {
            parentNode->leftChild->parent = parentNode;
        }
        pivot->rightChild = parentNode;
        parentNode->parent = pivot;

        if (pivot->parent == nullptr) {
            m_root = pivot;
        }

        pivot->rightChild->level = std::max(
                pivot->rightChild->getLeftChildLevel() + 1,
                pivot->rightChild->getRightChildLevel() + 1);
        pivot->level = std::max(
                pivot->getLeftChildLevel() + 1,
                pivot->getRightChildLevel() + 1);
    }

    std::vector<T> getInOrder() {
        std::vector<T> result;
        result.reserve(m_size);
        doGetInOrder(m_root, result);
        return result;
    }

    std::vector<T> getPreOrder() {
        std::vector<T> result;
        result.reserve(m_size);
        doGetPreOrder(m_root, result);
        return result;
    }
protected:
    void doGetPreOrder(AVLNode* node, std::vector<T>& result) {
        if (node == nullptr) {
            return;
        }
        result.push_back(node->value);
        doGetPreOrder(node->leftChild, result);
        doGetPreOrder(node->rightChild, result);
    }

    void doGetInOrder(AVLNode* node, std::vector<T>& result) {
        if (node == nullptr) {
            return;
        }
        doGetInOrder(node->leftChild, result);
        result.push_back(node->value);
        doGetInOrder(node->rightChild, result);
    }

private:
    std::size_t m_size;
    AVLNode* m_root;

    struct AVLNode
    {
        AVLNode* parent;
        AVLNode* leftChild;
        AVLNode* rightChild;
        std::size_t level;
        std::size_t count;
        T value;
        AVLNode(const T& value)
            :value(value),
            level(1),
            count(1),
            parent(nullptr),
            leftChild(nullptr),
            rightChild(nullptr)
        {
        }

        std::size_t getLeftChildLevel() {
            if (leftChild == nullptr) {
                return 0;
            }
            return leftChild->level;
        }

        std::size_t getRightChildLevel() {
            if (rightChild == nullptr) {
                return 0;
            }
            return rightChild->level;
        }
    };

    void deleteNodes() noexcept {
        if (m_root != nullptr) {
            std::stack<AVLNode*> nodes;
            nodes.push(m_root);
            while (!nodes.empty()) {
                AVLNode* node = nodes.top();
                nodes.pop();
                if (node->leftChild != nullptr) {
                    nodes.push(node->leftChild);
                    node->leftChild = nullptr;
                }

                if (node->rightChild != nullptr) {
                    nodes.push(node->rightChild);
                    node->rightChild = nullptr;
                }

                delete node;
                node = nullptr;
            }
        }
    }

    void traverseNodes() {
        AVLNode* node = m_root;
        do {
            std::cout << std::endl;
            std::cout << "Node " << node->value << " ";
            if (node->parent == nullptr)
                std::cout << "\nParent: " << nullptr;
            else
                std::cout << "\nParent: " << node->parent->value;
            if (node->leftChild == nullptr)
                std::cout << "\nLeft child: " << nullptr;
            else
                std::cout << "\nLeft child: " << node->leftChild->value;

            if (node->rightChild == nullptr)
                std::cout << "\nRight child: " << nullptr;
            else
                std::cout << "\nRight child: " << node->rightChild->value;
            std::cout << std::endl;
            std::string c;
            std::cin >> c;
            if (c == "l")
                node = node->leftChild;
            else if (c == "r")
                node = node->rightChild;
            else if (c == "u")
                node = node->parent;
            else
                break;
        } while (true);
    }
};

#endif
