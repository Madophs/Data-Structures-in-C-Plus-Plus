#ifndef __AVL_TREE__
#define __AVL_TREE__

#include <cstddef>
#include <initializer_list>
#include <iostream>
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
        doDeleteNodes();
    }

    std::size_t size() const {
        return m_size;
    }

    std::size_t empty() const {
        return m_size == 0;
    }

    int getHeight() noexcept {
        if (m_root == nullptr)
            return 0;
        return getHeight(m_root->value);
    }

    int getHeight(const T &value) noexcept {
        auto itemPtr = doFind(value);
        if (itemPtr == nullptr)
            return -1;
        return itemPtr->height;
    }

    bool exists(const T &value) noexcept {
        return doFind(value) != nullptr;
    }

    void insert(const T& value) {
        if (m_root == nullptr) {
            m_root = new AVLNode(value);
            ++m_size;
        } else {
            AVLNode *parentNode = m_root;
            AVLNode *childNode = m_root;
            while (childNode != nullptr) {
                parentNode = childNode;
                if (value < childNode->value) {
                    childNode = childNode->leftChild;
                } else if (value > childNode->value) {
                    childNode = childNode->rightChild;
                } else {
                    break;
                }
            }

            if (value < parentNode->value) {
                parentNode->leftChild = new AVLNode(value);
                parentNode->leftChild->parent = parentNode;
                ++m_size;
                doBalance(parentNode->leftChild);
            } else if (value > parentNode->value) {
                parentNode->rightChild = new AVLNode(value);
                parentNode->rightChild->parent = parentNode;
                ++m_size;
                doBalance(parentNode->rightChild);
            } else {
                ++parentNode->count;
            }
        }
    }

    void remove(const T& value) {
        if (m_root == nullptr) {
            throw std::runtime_error("AVL is empty.");
        }

        AVLNode *targetNode = doFind(value);
        if (targetNode == nullptr) {
            throw std::runtime_error("remove: element doesn't exists.");
        }

        if (targetNode->leftChild == nullptr || targetNode->rightChild == nullptr) {
            AVLNode *successor = targetNode->leftChild ? targetNode->leftChild : targetNode->rightChild;
            if (successor != nullptr) {
                doUpdateParent(targetNode->parent, successor);
                doBalance(successor);
                if (successor->parent == nullptr) {
                    m_root = successor;
                }
            } else {
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
                doBalance(parentNode);
            }

            delete targetNode;
            --m_size;

            return;
        }

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
            doBalance(successor->rightChild);
        } else if (successor->leftChild != nullptr) {
            doBalance(successor->leftChild);
        } else {
            doBalance(successor);
        }

        delete targetNode;
        --m_size;
        return;
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
            std::cout << "Height: " << node->height << std::endl;
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
    void doBalance(AVLNode *traversalNode) {
        while (traversalNode != nullptr) {
            doUpdateHeights(traversalNode);
            int balanceDiff = traversalNode->getBalanceDiff();
            if (balanceDiff == -2) {
                int balanceChildDiff = traversalNode->rightChild->getBalanceDiff();
                if (balanceChildDiff == 1) {
                    doRightRotation(&traversalNode->rightChild);
                    doLeftRotation(&traversalNode);
                } else {
                    doLeftRotation(&traversalNode);
                }
            } else if (balanceDiff == 2) {
                int balanceChildDiff = traversalNode->leftChild->getBalanceDiff();
                if (balanceChildDiff == -1) {
                    doLeftRotation(&traversalNode->leftChild);
                    doRightRotation(&traversalNode);
                } else {
                    doRightRotation(&traversalNode);
                }
            }
            traversalNode = traversalNode->parent;
        }
    }

    void doLeftRotation(AVLNode **node) {
        AVLNode *parentNode = (*node)->parent;
        AVLNode *pivot = (*node)->rightChild;

        (*node)->rightChild = pivot->leftChild;
        if ((*node)->rightChild != nullptr) {
            (*node)->rightChild->parent = *node;
        }
        pivot->leftChild = *node;
        (*node)->parent = pivot;

        doUpdateParent(parentNode, pivot);

        *node = pivot;

        if (pivot->parent == nullptr) {
            m_root = pivot;
        }

        doUpdateHeights(pivot);
    }

    void doRightRotation(AVLNode **node) {
        AVLNode *parentNode = (*node)->parent;
        AVLNode *pivot = (*node)->leftChild;

        (*node)->leftChild = pivot->rightChild;
        if ((*node)->leftChild != nullptr) {
            (*node)->leftChild->parent = *node;
        }
        pivot->rightChild = *node;
        (*node)->parent = pivot;

        doUpdateParent(parentNode, pivot);

        *node = pivot;

        if (pivot->parent == nullptr) {
            m_root = pivot;
        }

        doUpdateHeights(pivot);
    }

    void doUpdateHeights(AVLNode *node) noexcept {
        if (node->leftChild != nullptr)
            node->leftChild->updateHeight();

        if (node->rightChild != nullptr)
            node->rightChild->updateHeight();

        node->updateHeight();
    }

    AVLNode * doFind(const T &value) noexcept {
        if (m_root == nullptr)
            return nullptr;

        AVLNode *traversalNode = m_root;
        while (traversalNode != nullptr) {
            if (value == traversalNode->value) {
                return traversalNode;
            } else if (value < traversalNode->value) {
                traversalNode = traversalNode->leftChild;
            } else {
                traversalNode = traversalNode->rightChild;
            }
        }

        return nullptr;
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

    void doDeleteNodes() noexcept {
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

    inline void doUpdateParent(AVLNode *parent, AVLNode *child) {
        child->parent = parent;
        if (parent == nullptr)
            return;
        if (child->value < parent->value)
            parent->leftChild = child;
        else
            parent->rightChild = child;
    }

    struct AVLNode
    {
        AVLNode *parent;
        AVLNode *leftChild;
        AVLNode *rightChild;
        std::size_t height;
        std::size_t count;
        T value;
        AVLNode(const T& value)
            :value(value),
            height(1),
            count(1),
            parent(nullptr),
            leftChild(nullptr),
            rightChild(nullptr)
        {
        }

        std::size_t getLeftChildHeight() const noexcept {
            if (leftChild == nullptr) {
                return 0;
            }
            return leftChild->height;
        }

        std::size_t getRightChildHeight() const noexcept {
            if (rightChild == nullptr) {
                return 0;
            }
            return rightChild->height;
        }

        inline int getBalanceDiff() noexcept {
            return getLeftChildHeight() - getRightChildHeight();
        }

        void updateHeight() noexcept {
            height = std::max(getLeftChildHeight() + 1, getRightChildHeight() + 1);
        }
    };
};

#endif
