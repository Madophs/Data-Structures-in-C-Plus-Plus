#include <exception>
#include <stdexcept>
#include <iostream>
#include <ostream>
#include <queue>
#include <vector>

using namespace std;

template <typename T>
struct Node
{
    T m_value;
    Node *m_right, *m_left, *m_parent;
    explicit Node(T i_value):m_value(i_value), m_right(nullptr), m_left(nullptr), m_parent(nullptr) {}
    friend ostream& operator<<(ostream &out, const Node<T>* node) { out << node->m_value; return out; }
    bool operator <(Node<T> i_node) { return m_value < i_node.m_value; }
    bool operator <=(Node<T> i_node) { return m_value <= i_node.m_value; }
    bool operator >(Node<T> i_node) { return m_value > i_node.m_value; }
    bool operator >=(Node<T> i_node) { return m_value >= i_node.m_value; }
    bool operator !=(Node<T> i_node) { return m_value != i_node.m_value; }
    bool operator ==(Node<T> i_node) { return m_value == i_node.m_value; }
};


/**
 * brief: Simple Binary Search Tree that allows duplicate values
 */
template <typename T>
class BST
{
    public:
        BST():m_root(nullptr)
        {
            m_size = 0;
        }

        ~BST()
        {
            do_postOrderDelete(m_root);
        }

        void insert(const T& i_newValue)
        {
            Node<T>* newNode = new Node<T>(i_newValue);
            if (m_root == nullptr) {
                m_root = newNode;
            } else {
                Node<T>* upfrontNode = m_root;
                Node<T>* prevNode = upfrontNode;
                while (upfrontNode != nullptr) {
                    prevNode = upfrontNode;
                    if (*newNode < *upfrontNode) {
                        upfrontNode = upfrontNode->m_left;
                    } else if (*newNode > *upfrontNode) {
                        upfrontNode = upfrontNode->m_right;
                    } else {
                        break;
                    }
                }

                if (*newNode == *prevNode) {
                    while (prevNode->m_left != nullptr && *newNode == *prevNode->m_left) {
                        prevNode = prevNode->m_left;
                    }
                    newNode->m_parent = prevNode;
                    if (prevNode->m_left != nullptr) {
                        newNode->m_left = prevNode->m_left;
                        newNode->m_left->m_parent = newNode;
                    }
                    prevNode->m_left = newNode;
                } else if (*newNode < *prevNode) {
                    prevNode->m_left = newNode;
                } else {
                    prevNode->m_right = newNode;
                }
                newNode->m_parent = prevNode;
            }
            ++m_size;
        }

        bool erase(const T& i_toDelete)
        {
            // Traverse the tree to look for the first occurrence of i_toDelete
            Node<T>* upfrontNode = m_root;
            Node<T>* parentNode = upfrontNode;
            while (upfrontNode != nullptr && i_toDelete != upfrontNode->m_value) {
                parentNode = upfrontNode;
                if (i_toDelete < upfrontNode->m_value) {
                    upfrontNode = upfrontNode->m_left;
                } else {
                    upfrontNode = upfrontNode->m_right;
                }
            }

            if (upfrontNode == nullptr) return false; // Not found

            // Make sure to keep left/right nodes from target node
            // Later will be appended to the future parent node
            Node<T>* leftChild = nullptr;
            Node<T>* rightChild = upfrontNode->m_right;
            queue<Node<T>*> itemsToDelete;
            while (upfrontNode != nullptr && i_toDelete == upfrontNode->m_value) {
                itemsToDelete.push(upfrontNode);
                upfrontNode = upfrontNode->m_left;
            }
            leftChild = upfrontNode;

            // Avoid to point to a possible future invalid pointer
            if (i_toDelete < parentNode->m_value) {
                parentNode->m_left = nullptr;
            } else if (i_toDelete > parentNode->m_value) {
                parentNode->m_right = nullptr;
            }

            // Right child becomes the new parent
            if (rightChild != nullptr) {
                // Left child is appended in right child's leftmost leaf
                // As for obvious reasons all left child nodes have lower values
                Node<T>* leftmostChild = rightChild;
                while (leftmostChild->m_left != nullptr) {
                    leftmostChild = leftmostChild->m_left;
                }
                leftmostChild->m_left = leftChild;
                leftChild->m_parent = leftmostChild;

                parentNode->m_left = rightChild;
                rightChild->m_parent = parentNode;

                // Special case where the target node is the root, so the right child takes its place
                if (i_toDelete == parentNode->m_value) {
                    rightChild->m_parent = nullptr;
                    m_root = rightChild;
                }
            } else if (leftChild != nullptr) {
                parentNode->m_left = leftChild;
                leftChild->m_parent = parentNode;
                // Special case where the target node is the root, so the left child takes its place
                if (i_toDelete == parentNode->m_value) {
                    leftChild->m_parent = nullptr;
                    m_root = leftChild;
                }
            }

            // Now is safe to delete the target nodes :)
            while (!itemsToDelete.empty()) {
                Node<T>* item = itemsToDelete.front();
                item->m_parent = nullptr;
                itemsToDelete.pop();
                delete item;
            }
            ++m_size;
            return true;
        }

        vector<T> getPreOrder()
        {
            vector<T> res;
            do_preOrder(m_root, res);
            return res;
        }

        // InOrder always returns the elements sorted
        vector<T> getInOrder()
        {
            vector<T> res;
            do_inOrder(m_root, res);
            return res;
        }

        bool isEmpty() { return m_size == 0; }

        uint32_t size() const { return size; }

    protected:
        void do_preOrder(Node<T> *&i_node, vector<T> &res)
        {
            if (i_node == nullptr) return;
            res.push_back(i_node->m_value);
            do_preOrder(i_node->m_left, res);
            do_preOrder(i_node->m_right, res);
        }

        void do_inOrder(Node<T> *&i_node, vector<T> &res)
        {
            if (i_node == nullptr) return;
            do_inOrder(i_node->m_left, res);
            res.push_back(i_node->m_value);
            do_inOrder(i_node->m_right, res);
        }

        void do_postOrderDelete(Node<T> *i_node)
        {
            if (i_node == nullptr) return;
            do_postOrderDelete(i_node->m_left);
            do_postOrderDelete(i_node->m_right);
            delete i_node;
            i_node = nullptr;
        }
    private:
        Node<T> *m_root;
        uint32_t m_size;
};
