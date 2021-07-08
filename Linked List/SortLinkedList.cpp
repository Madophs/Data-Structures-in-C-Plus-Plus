#include <iostream>

using namespace std;

struct Node {
    int val;
    Node *next_ptr;
    Node (int val)
    {
        this->val = val;
        this->next_ptr = nullptr;
    }
};

class LinkedList
{
    public:
        LinkedList()
        {
            m_head = m_tail = nullptr;
        }

        ~LinkedList()
        {
            Node *nodeIter = m_head;

            while (nodeIter)
            {
                Node *nodeToDel = nodeIter;

                if ((nodeIter)->next_ptr)
                    nodeIter = nodeIter->next_ptr;
                else
                    nodeIter = nullptr;

                delete nodeToDel;
                nodeToDel = nullptr;
            }
        }

        void pushBack(int item)
        {
            if (m_head)
            {
                if (item < m_head->val)
                {
                    Node *newHead = new Node(item);
                    newHead->next_ptr = m_head;
                    m_head = newHead;
                }
                else if (item > m_tail->val)
                {
                    m_tail->next_ptr = new Node(item);
                    m_tail = m_tail->next_ptr;
                }
                else
                {
                    Node **tracer = &m_head;

                    while (tracer && item > (**tracer).val)
                    {
                        tracer = &(*tracer)->next_ptr;
                    }

                    Node *newNode = new Node(item);
                    newNode->next_ptr = *tracer;
                    *tracer = newNode;
                }
            }
            else
            {
                m_head = new Node(item);
                m_tail = m_head;
            }
        }

        void print()
        {
            for (Node *iter = m_head; iter; iter = iter->next_ptr)
                cout << iter->val << " ";
            cout << endl;
        }

    private:
        Node *m_head, *m_tail;
};

int main()
{
    int item;
    LinkedList myList;
    while (cin >> item)
    {
        myList.pushBack(item);
    }

    myList.print();

    return 0;
}
