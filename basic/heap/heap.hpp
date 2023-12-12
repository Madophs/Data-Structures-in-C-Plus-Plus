#ifndef  __HEAP_H__
#define __HEAP_H__

#include <cstdint>
#include <iostream>
#include <deque>

using namespace std;

template <class T>
class Heap
{
    public:
        Heap();

        template <class Comparator>
        Heap(Comparator cmp);

        template <class InputIterator>
        Heap(InputIterator begin, InputIterator end);

        template <class InputIterator, class Comparator>
        Heap(InputIterator begin, InputIterator end, Comparator cmp);

        typename deque<T>::iterator begin() noexcept;

        typename deque<T>::iterator end() noexcept;

        template <class SimpleIterator>
        SimpleIterator end();

        void insert(const T& item);

        T pop();

        T top() const;

        T operator[](uint32_t index) const { return m_container[index]; }

        inline uint32_t size() const;

        inline bool empty() const;

        void clear();
    protected:
        void doBubbleUp(uint32_t index);

        void doBubbleDown(uint32_t index);

        inline uint32_t doGetParent(const uint32_t& index);

        inline uint32_t doGetLeftChild(const uint32_t& index);

        inline uint32_t doGetRightChild(const uint32_t& index);

        inline static bool doDefaultCmp(const T& a, const T& b);
    private:
        deque<T> m_container;

        bool (*m_cmp) (const T&, const T&);

        const uint32_t ROOT{0};
};

template <class T>
Heap<T>::Heap()
{
    m_cmp = &doDefaultCmp;
}

template <class T>
template <class Comparator>
Heap<T>::Heap(Comparator cmp)
{
    m_cmp = cmp;
}

template <class T>
template <class InputIterator>
Heap<T>::Heap(InputIterator begin, InputIterator end)
{
    m_cmp = &doDefaultCmp;
    for (;begin != end; ++begin) {
        insert(*begin);
    }
}

template <class T>
template <class InputIterator, class Comparator>
Heap<T>::Heap(InputIterator begin, InputIterator end, Comparator cmp)
{
    m_cmp = cmp;
    for (;begin != end; ++begin) {
        insert(*begin);
    }
}

template <class T>
typename deque<T>::iterator Heap<T>::begin() noexcept
{
    return m_container.begin();
}

template <class T>
typename deque<T>::iterator Heap<T>::end() noexcept
{
    return m_container.end();
}

template <class T>
void Heap<T>::insert(const T& item)
{
    m_container.push_back(item);
    doBubbleUp(m_container.size()-1);
}

template <class T>
T Heap<T>::pop()
{
    swap(m_container.front(), m_container.back());
    T item = m_container.back();
    m_container.pop_back();
    doBubbleDown(ROOT);
    return item;
}

template <class T>
T Heap<T>::top() const
{
    return m_container.front();
}

template <class T>
uint32_t Heap<T>::size() const
{
    return m_container.size();
}

template <class T>
bool Heap<T>::empty() const
{
    return m_container.empty();
}

template <class T>
void Heap<T>::clear()
{
    m_container.clear();
}

// Protected Methods

template <class T>
void Heap<T>::doBubbleUp(uint32_t index)
{
    uint32_t parentIndex = doGetParent(index);
    while (m_cmp(m_container[index], m_container[parentIndex])) {
        swap(m_container[index], m_container[parentIndex]);
        index = parentIndex;
        parentIndex = doGetParent(index);
    }
}

template <class T>
void Heap<T>::doBubbleDown(uint32_t index)
{
    uint32_t parent = index;
    uint32_t leftChild = doGetLeftChild(parent);
    uint32_t rightChild = doGetRightChild(parent);
    bool onLeft = leftChild < m_container.size() ? m_cmp(m_container[leftChild], m_container[parent]) : false;
    bool onRight = rightChild < m_container.size() ? m_cmp(m_container[rightChild], m_container[parent]) : false;
    do {
        if (onLeft && onRight) {
            if (m_cmp(m_container[leftChild], m_container[rightChild])) {
                doBubbleUp(leftChild);
                parent = leftChild;
            } else {
                doBubbleUp(rightChild);
                parent = rightChild;
            }
        } else {
            if (onLeft) {
                doBubbleUp(leftChild);
                parent = leftChild;
            } else if (onRight) {
                doBubbleUp(rightChild);
                parent = rightChild;
            }
        }
        leftChild = doGetLeftChild(parent);
        rightChild = doGetRightChild(parent);
        onLeft = leftChild < m_container.size() ? m_cmp(m_container[leftChild], m_container[parent]) : false;
        onRight = rightChild < m_container.size() ? m_cmp(m_container[rightChild], m_container[parent]) : false;
    } while (onLeft || onRight);
}

template <class T>
bool Heap<T>::doDefaultCmp(const T&a, const T&b)
{
    return a > b;
}

template <class T>
uint32_t Heap<T>::doGetParent(const uint32_t& index)
{
    if (index == 0) return 0;
    return (index - 1) >> 1;
}

template <class T>
uint32_t Heap<T>::doGetLeftChild(const uint32_t& index)
{
    return (index << 1) + 1;
}

template <class T>
uint32_t Heap<T>::doGetRightChild(const uint32_t& index)
{
    return (index << 1) + 2;
}

#endif
