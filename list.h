//
// Created by chenchukun on 17/10/30.
//

#ifndef SIMPLESTL_LIST_H
#define SIMPLESTL_LIST_H

#include <memory>
#include <initializer_list>
#include "reverse_iterator.h"

#ifdef DEBUG
    #include <iostream>
#endif

namespace sstl
{

// 节点类型
template<typename T>
struct __ListNode
{
    __ListNode<T> *prev;    // 前驱指针
    __ListNode<T> *next;    // 后继指针

    T data;     // 数据成员
};


// 迭代器类型
// Ref和Ptr用来区分const_iterator和iterator
template<typename T, typename Ref, typename Ptr>
class __ListIterator
{
public:
    typedef T value_type;
    typedef Ptr point;
    typedef Ref reference;
    typedef __ListNode<T> Node;
    typedef __ListIterator self;

    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    __ListIterator(Node *node): pNode(node) {}

    __ListIterator() {}

    __ListIterator(const self &iter): pNode(iter.pNode) {}

    self& operator=(const self &right) {
        pNode = right.pNode;
        return *this;
    }

    self& operator++() {
        pNode = pNode->next;
        return *this;
    }

    self operator++(int) {
        self ret = *this;
        pNode = pNode->next;
        return ret;
    }

    self& operator--() {
        pNode = pNode->prev;
        return *this;
    }

    self operator--(int) {
        self ret = *this;
        pNode = pNode->prev;
        return ret;
    }

    bool operator==(const self &right) const {
        return pNode == right.pNode;
    }

    bool operator!=(const self &right) const {
        return !(*this == right);
    }

    // const_iterator返回const T&, iterator返回T&
    reference operator*() const {
        return pNode->data;
    }

    // const_iterator返回const T*, iterator返回T*
    point operator->() const {
        return &(operator*());
    }

private:
    Node *pNode;    // 指向链表节点类型
};


template<typename T, typename Alloc=std::allocator<__ListNode<T> > >
class list
{
public:
    typedef T value_type;
    typedef T* point;
    typedef const T* const_point;
    typedef T& reference;
    typedef const T& const_reference;
    typedef __ListNode<T> ListNode;

    typedef __ListIterator<T, reference, point> iterator;
    typedef __ListIterator<T, const_reference, const_point> const_iterator;
    typedef reverse_iterator<const_iterator> const_reverse_iterator;
    typedef reverse_iterator<iterator> reverse_iterator;

    list():endNode(nullptr) {
        endNode = alloc.allocate(1);
        endNode->next = endNode->prev = endNode;
    }

    list(const std::initializer_list<T> &initList);

    iterator begin() {
        return iterator(endNode->next);
    }

    iterator end() {
        return iterator(endNode);
    }

    const_iterator cbegin() const {
        return const_iterator(endNode->next);
    }

    const_iterator cend() const {
        return const_iterator(endNode);
    }

    reverse_iterator rbegin() {
        return reverse_iterator(end());
    }

    reverse_iterator rend() {
        return reverse_iterator(begin());
    }

    const_reverse_iterator rcbegin() {
        return const_reverse_iterator(cend());
    }

    const_reverse_iterator rcend() {
        return const_reverse_iterator(cbegin());
    }

    ~list();

public:
    bool empty() const {
        return endNode->prev == endNode->next;
    }

private:
    ListNode *endNode;

    Alloc alloc;        // 分配器
};


template<typename T, typename Alloc >
list<T, Alloc>::~list()
{
    ListNode *head = endNode->next;
    while (head != endNode) {
        ListNode *tmp = head;
        head = head->next;
        alloc.destroy(tmp);
        alloc.deallocate(tmp, 1);
    }
    alloc.destroy(endNode);
    alloc.deallocate(endNode, 1);
#ifdef DEBUG
    std::cout << "~list()" << std::endl;
#endif
}

template<typename T, typename Alloc>
list<T, Alloc>::list(const std::initializer_list<T> &initList)
    :list()
{
    for (auto &item : initList) {
        ListNode *node = alloc.allocate(1);
        node->data = item;
        ListNode *tail = endNode->prev;
        node->next = endNode;
        node->prev = tail;
        endNode->prev = node;
        tail->next = node;
    }
}

}


#endif //SIMPLESTL_LIST_H
