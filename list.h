//
// Created by chenchukun on 17/10/30.
//

#ifndef SIMPLESTL_LIST_H
#define SIMPLESTL_LIST_H

#include <memory>

namespace sstl
{
// 节点类型
template<typename T>
struct __ListNode
{
    __ListNode(): prev(nullptr), next(nullptr) {}

    T data;     // 数据成员
    __ListNode<T> *prev;    // 前驱指针
    __ListNode<T> *next;    // 后继指针
};

template<typename T>
struct __ListIterator
{
public:
    typedef T value_type;
    typedef T* point;
    typedef const T* const_point;
    typedef T& reference;
    typedef const T& const_reference;
private:

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

    typedef __ListIterator<T> iterator;
    typedef __ListIterator<const T> const_iterator;

    list():headNode(nullptr) {
        headNode = alloc.allocate(1);
        alloc.construct(headNode);
        headNode->next = headNode->prev = headNode;
    }

    ~list() {
        ListNode *head = headNode->next;
        while (head != headNode) {
            ListNode *tmp = head;
            head = head->next;
            alloc.destroy(tmp);
            alloc.deallocate(tmp, 1);
        }
        alloc.destroy(headNode);
        alloc.deallocate(headNode, 1);
    }

public:
    bool empty() const {
        return headNode->prev == headNode->next;
    }

private:
    ListNode *headNode;

    Alloc alloc;        // 分配器
};

}


#endif //SIMPLESTL_LIST_H
