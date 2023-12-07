#ifndef __AVL_TREE__
#define __AVL_TREE__

#include <cstddef>
#include <initializer_list>
#include <ios>
#include <iostream>
#include <iterator>
#include <stdexcept>
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

    bool exists(const T& value) {
        if (m_root == nullptr) {
            return false;
        }
        AVLNode *traversalNode = m_root;
        while (traversalNode != nullptr) {
            if (value == traversalNode->value) {
                return true;
            } else if (value < traversalNode->value) {
                traversalNode = traversalNode->leftChild;
            } else {
                traversalNode = traversalNode->rightChild;
            }
        }
        return false;
    }

    void insert(const T& value) {
        AVLNode *newNode = new AVLNode(value);
        if (m_root == nullptr) {
            m_root = newNode;
            ++m_size;
        } else {
            AVLNode *upfrontNode = m_root;
            AVLNode *prevNode = m_root;
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

            doRotate(newNode);
        }
    }

    void remove(const T& value) {
        std::cout << "Removing " << value << std::endl;
        if (m_root == nullptr) {
            throw std::runtime_error("AVL is empty.");
        }

        AVLNode *targetNode = m_root;
        while (targetNode != nullptr) {
            if (value == targetNode->value) {
                break;
            } else if (value < targetNode->value) {
                targetNode = targetNode->leftChild;
            } else {
                targetNode = targetNode->rightChild;
            }
        }

        if (targetNode == nullptr) {
            throw std::runtime_error("remove: element doesn't exists.");
        }

        if (targetNode->leftChild == nullptr && targetNode->rightChild == nullptr) {
            AVLNode *parentNode = targetNode->parent;
            if (parentNode != nullptr) {
                if (targetNode->value < parentNode->value) {
                    parentNode->leftChild = nullptr;
                } else {
                    parentNode->rightChild = nullptr;
                }
            } else {
                m_root = nullptr;
            }

            doRotate(parentNode);

            delete targetNode;
            --m_size;
            return;
        }

        if (targetNode->rightChild != nullptr) {
            AVLNode *successor = targetNode->rightChild;
            while (successor->leftChild != nullptr) {
                successor = successor->leftChild;
            }

            if (successor->parent->value != targetNode->value) {
                AVLNode *parent = successor->parent;
                parent->leftChild = successor->rightChild;
                if (parent->leftChild != nullptr) {
                    parent->leftChild->parent = parent;
                }

                successor->rightChild = targetNode->rightChild;
                successor->rightChild->parent = successor;
            }

            successor->leftChild = targetNode->leftChild;
            if (successor->leftChild != nullptr) {
                successor->leftChild->parent = successor;
            }

            successor->parent = targetNode->parent;
            if (successor->parent != nullptr) {
                if (successor->value < successor->parent->value) {
                    successor->parent->leftChild = successor;
                } else {
                    successor->parent->rightChild = successor;
                }
            } else {
                m_root = successor;
            }

            if (successor->rightChild != nullptr) {
                doRotate(successor->rightChild);
            } else if (successor->leftChild != nullptr) {
                doRotate(successor->leftChild);
            } else {
                doRotate(successor);
            }

            delete targetNode;
            --m_size;
            return;
        }

        if (targetNode->leftChild != nullptr) {
            AVLNode *leftChild = targetNode->leftChild;

            leftChild->rightChild = targetNode->rightChild;
            if (leftChild->rightChild != nullptr) {
                leftChild->rightChild->parent = leftChild;
            }
            leftChild->parent = targetNode->parent;
            if (leftChild->parent != nullptr) {
                if (leftChild->value < leftChild->parent->value) {
                    leftChild->parent->leftChild = leftChild;
                } else {
                    leftChild->parent->rightChild = leftChild;
                }
            } else {
                m_root = leftChild;
            }

            doRotate(leftChild);

            delete targetNode;
            --m_size;
        }
    }

    std::vector<T> getPreOrder() {
        std::vector<T> result;
        result.reserve(m_size);
        doGetPreOrder(m_root, result);
        return result;
    }

    std::vector<T> getInOrder() {
        std::vector<T> result;
        result.reserve(m_size);
        doGetInOrder(m_root, result);
        return result;
    }

    std::vector<T> getPostOrder() {
        std::vector<T> result;
        result.reserve(m_size);
        doGetPostOrder(m_root, result);
        return result;
    }

    void traverseNodes() {
        AVLNode *node = m_root;
        do {
            std::cout << std::endl;
            std::cout << "Node " << node->value << std::endl;
            std::cout << "Height: " << node->level << std::endl;
            if (node->parent == nullptr)
                std::cout << "Parent: " << nullptr;
            else
                std::cout << "Parent: " << node->parent->value;
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
protected:
    void doRotate(AVLNode *traversalNode) {
        if (traversalNode == nullptr) {
            return;
        }

        traversalNode->level = std::max(
                traversalNode->getLeftChildLevel() + 1,
                traversalNode->getRightChildLevel() + 1);

        while (traversalNode != nullptr && traversalNode->parent != nullptr) {
            AVLNode *parentNode = traversalNode->parent;
            parentNode->level = std::max(
                    parentNode->getLeftChildLevel() + 1,
                    parentNode->getRightChildLevel() + 1);
            int currentNodeDiff = traversalNode->getLeftChildLevel() - traversalNode->getRightChildLevel();
            int parentDiff = parentNode->getLeftChildLevel() - parentNode->getRightChildLevel();
            if (parentDiff == -2) {
                if (currentNodeDiff == 1) {
                    doRightRotation(traversalNode->leftChild);
                } else {
                    doLeftRotation(traversalNode);
                }
            } else if (parentDiff == 2) {
                if (currentNodeDiff == -1) {
                    doLeftRotation(traversalNode->rightChild);
                } else {
                    doRightRotation(traversalNode);
                }
            }
            traversalNode = traversalNode->parent;
        }
    }

    void doLeftRotation(AVLNode *pivot) {
        AVLNode *parentNode = pivot->parent;
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
        if (pivot->parent != nullptr) {
            pivot->parent->level = std::max(
                    pivot->parent->getLeftChildLevel() + 1,
                    pivot->parent->getRightChildLevel() + 1);
        }
    }

    void doRightRotation(AVLNode *pivot) {
        AVLNode *parentNode = pivot->parent;
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
        if (pivot->parent != nullptr) {
            pivot->parent->level = std::max(
                    pivot->parent->getLeftChildLevel() + 1,
                    pivot->parent->getRightChildLevel() + 1);
        }
    }

    void doGetPreOrder(AVLNode *node, std::vector<T>& result) {
        if (node == nullptr) {
            return;
        }
        result.push_back(node->value);
        doGetPreOrder(node->leftChild, result);
        doGetPreOrder(node->rightChild, result);
    }

    void doGetInOrder(AVLNode *node, std::vector<T>& result) {
        if (node == nullptr) {
            return;
        }
        doGetInOrder(node->leftChild, result);
        result.push_back(node->value);
        doGetInOrder(node->rightChild, result);
    }

    void doGetPostOrder(AVLNode *node, std::vector<T>& result) {
        if (node == nullptr) {
            return;
        }
        doGetPostOrder(node->leftChild, result);
        doGetPostOrder(node->rightChild, result);
        result.push_back(node->value);
    }

private:
    std::size_t m_size;
    AVLNode *m_root;

    struct AVLNode
    {
        AVLNode *parent;
        AVLNode *leftChild;
        AVLNode *rightChild;
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
                AVLNode *node = nodes.top();
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

};

#endif
