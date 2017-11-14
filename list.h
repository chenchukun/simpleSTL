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

template <typename T, typename Alloc> class list;

// 迭代器类型
// Ref和Ptr用来区分const_iterator和iterator
// const_iterator无法赋值给iterator,如何实现?
template<typename T, typename Ref, typename Ptr>
class __ListIterator
{
public:
    friend class list<T, std::allocator<T> >;

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

// 双向循环链表
template<typename T, typename Alloc=std::allocator<T> >
class list
{
public:

    template<typename _T, typename _Alloc>
    friend std::ostream& operator<<(std::ostream &out, const list<_T, _Alloc> &l);

    typedef T value_type;
    typedef T* point;
    typedef const T* const_point;
    typedef T& reference;
    typedef const T& const_reference;
    typedef __ListNode<T> ListNode;
    typedef list self;

    typedef __ListIterator<T, reference, point> iterator;
    typedef __ListIterator<T, const_reference, const_point> const_iterator;
    typedef reverse_iterator<const_iterator> const_reverse_iterator;
    typedef reverse_iterator<iterator> reverse_iterator;

    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    typedef std::allocator<ListNode> NodeAlloc;
    typedef Alloc allocator_type;

    /*  构造函数和析构函数 */
    // 构造空列表
    list():endNode(nullptr) {
        endNode = NodeAlloc().allocate(1);
        endNode->next = endNode->prev = endNode;
    }

    // 用一个initializer_list初始化改列表
    list(const std::initializer_list<T> &initList);

    /*
    list(const_iterator first, const_iterator last);

    list(iterator first, iterator last);

    list(const_point first, const_point last);
    */

    // 构造n个使用默认构造函数构造的元素的列表
    list(size_type n);

    // 元素为数值类型时,与模板类型的构造函数冲突,这个如何解决?
    list(size_type n, const_reference data);

    // 接收类迭代器对的构造函数
    template<typename Iter>
    list(Iter first, Iter last);

    list(const self &right);

    self& operator=(const self &right);

    ~list();

    allocator_type get_allocator() const {
        return Alloc();
    }

    /* 获取迭代器 */
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

    bool empty() const {
        return endNode->prev == endNode->next;
    }

    size_type size() const {
        return distance(this->cbegin(), this->cend());
    }

    size_type max_size() {
        return size_type(-1);
    }

    // 清空列表
    void clear();

    // 在指定迭代器前插入元素,返回新插入的迭代器
    iterator insert(iterator it, const_reference data=value_type());

    // 同理,元素为整数类型时以下两个会有冲突,如何解决?
    // 在指定迭代器前插入n个元素,返回插入的最左的元素的迭代器
    iterator insert(iterator it, size_type n, const_reference data=value_type());

    // 将迭代器范围内的元素插入到指定迭代器前,返回插入的最左的元素的迭代器
    template<typename Iter>
    iterator insert(iterator it, Iter first, Iter last);

    void push_back(const_reference data);

    void push_front(const_reference data);

    iterator erase(iterator it);

    iterator erase(iterator first, iterator last);

    void pop_back();

    void pop_front();

    reference front() {
        return *begin();
    }

    const_reference front() const {
        return *cbegin();
    }

    reference back() {
        return *(--end());
    }

    const_reference back() const {
        return *(--cend());
    }

    // 将first和last指定的迭代器返回的节点移动到it迭代器前
    void transfer(iterator it, iterator first, iterator last);

    // 将列表归并到当前列表
    template <typename Compare>
    void merge(list &sl, Compare comp);

    // 删除元素值等于value的节点
    void remove(const_reference value);

    // 删除符合指定谓词的节点
    template<typename Predicate>
    void remove_if(Predicate pred);

    template <typename Compare>
    void sort();

    void swap(list& l);

    template <class BinaryPredicate>
    void unique(BinaryPredicate binaryPred);

private:
    ListNode *endNode;

private:
    // 构造一个节点
    ListNode* createNode(const_reference data) {
        ListNode *node = NodeAlloc().allocate(1);
        Alloc().construct(&node->data, data);
        return node;
    }

    // 求两个迭代器之间的距离
    size_type distance(const_iterator b, const_iterator e) const;

    ListNode* insert(ListNode *node, const_reference data);
};

template<typename T, typename Alloc >
list<T, Alloc>::~list()
{
    clear();
    NodeAlloc().deallocate(endNode, 1);
}

template<typename T, typename Alloc>
list<T, Alloc>::list(const std::initializer_list<T> &initList)
    : list()
{
    for (auto &item : initList) {
        ListNode *node = createNode(item);
        ListNode *tail = endNode->prev;
        node->next = endNode;
        node->prev = tail;
        endNode->prev = node;
        tail->next = node;
    }
}

/*
template<typename T, typename Alloc>
list<T, Alloc>::list(const_iterator first, const_iterator last)
    : list()
{
    const_iterator it = first;
    while (it != last) {
        insert(end(), *it++);
    }
}

template<typename T, typename Alloc>
list<T, Alloc>::list(iterator first, iterator last)
    : list()
{
    iterator it = first;
    while (it != last) {
        insert(end(), *it++);
    }
}

template<typename T, typename Alloc>
list<T, Alloc>::list(const_point first, const_point last)
    : list()
{
    const_point p = first;
    while (p != last) {
        insert(end(), *p++);
    }
}
*/

template<typename T, typename Alloc>
list<T, Alloc>::list(size_type n, const_reference data)
    : list()
{
    while (n--) {
        insert(end(), data);
    }
}

template<typename T, typename Alloc>
list<T, Alloc>::list(size_type n)
        : list()
{
    while (n--) {
        insert(end(), T());
    }
}

template<typename T, typename Alloc>
template<typename Iter>
list<T, Alloc>::list(Iter first, Iter last)
    : list()
{
    Iter it = first;
    while (it != last) {
        insert(end(), *it++);
    }
}

template<typename T, typename Alloc>
list<T, Alloc>::list(const self &right)
    : list()
{
    const_iterator it = right.cbegin();
    while (it != right.cend()) {
        insert(end(), *it++);
    }
}

template<typename T, typename Alloc>
typename list<T, Alloc>::self& list<T, Alloc>::operator=(const self &right)
{
    ListNode *currNode = right.endNode->next;
    ListNode *newEndNode = NodeAlloc().allocate(1);
    ListNode *prevNode = newEndNode;

    while (currNode != right.endNode) {
        ListNode *node = createNode(currNode->data);
        prevNode->next = node;
        node->prev = prevNode;
        prevNode = node;
        currNode = currNode->next;
    }
    prevNode->next = newEndNode;
    newEndNode->prev = prevNode;
    clear();
    NodeAlloc().deallocate(endNode, 1);
    endNode = newEndNode;
    return *this;
}

template<typename T, typename Alloc>
void list<T, Alloc>::clear()
{
    ListNode *head = endNode->next;
    while (head != endNode) {
        ListNode *tmp = head;
        head = head->next;
        NodeAlloc().destroy(tmp);
        NodeAlloc().deallocate(tmp, 1);
    }
    endNode->next = endNode->prev = endNode;
}

template<typename T, typename Alloc>
typename list<T, Alloc>::ListNode* list<T, Alloc>::insert(ListNode *node, const_reference data)
{
    ListNode *newNode = createNode(data);
    newNode->next = node;
    newNode->prev = node->prev;
    node->prev->next = newNode;
    node->prev = newNode;
    return newNode;
}

// 返回值类型为类内的typedef时,需要加typename
template<typename T, typename Alloc>
typename list<T, Alloc>::iterator list<T, Alloc>::insert(iterator it, const_reference data)
{
    return iterator(insert(it.pNode, data));
}

template<typename T, typename Alloc>
typename list<T, Alloc>::iterator list<T, Alloc>::insert(iterator it, size_type n, const_reference data)
{
    while (n--) {
        it = insert(it, data);
    }
    return it;
}

template<typename T, typename Alloc>
template<typename Iter>
typename list<T, Alloc>::iterator list<T, Alloc>::insert(iterator it, Iter first, Iter last)
{
    while (first != last) {
        it = insert(it, *first++);
    }
    return it;
}

template<typename T, typename Alloc>
typename list<T, Alloc>::size_type list<T, Alloc>::distance(const_iterator b, const_iterator e) const
{
    const_iterator it = b;
    size_type dis = 0;
    while (it != e) {
        ++it;
        ++dis;
    }
    return dis;
}

template<typename T, typename Alloc>
void list<T, Alloc>::push_back(const_reference data)
{
    insert(end(), data);
}

template<typename T, typename Alloc>
void list<T, Alloc>::push_front(const_reference data)
{
    insert(begin(), data);
}

template<typename T, typename Alloc>
typename list<T, Alloc>::iterator list<T, Alloc>::erase(iterator it)
{
    if (it == end()) {
        return it;
    }
    iterator ret = it;
    ++ret;
    ListNode *node = it.pNode;
    node->prev->next = node->next;
    node->next->prev = node->prev;
    Alloc().destroy(&node->data);
    NodeAlloc().deallocate(node, 1);
    return ret;
}

template<typename T, typename Alloc>
typename list<T, Alloc>::iterator list<T, Alloc>::erase(iterator first, iterator last)
{
    while (first != last) {
        erase(first++);
    }
    return last;
}

template<typename T, typename Alloc>
void list<T, Alloc>::pop_back()
{
    erase(--end());
}

template<typename T, typename Alloc>
void list<T, Alloc>::pop_front()
{
    erase(begin());
}

template<typename T, typename Alloc>
std::ostream& operator<<(std::ostream &out, const list<T, Alloc> &l)
{
    out << "(";
    auto it = l.cbegin();
    if (it != l.cend()) {
        out << *it++;
    }
    while (it != l.cend()) {
        out << ", " << *it++;
    }
    out << ")";
    return out;
}

template<typename T, typename Alloc>
void list<T, Alloc>::transfer(iterator it, iterator first, iterator last)
{
    ListNode *node = it.pNode;
    while (first != last) {
        ListNode *insNode = first.pNode;
        ++first;
        insNode->next = node;
        insNode->prev = node->prev;
        node->prev->next = node;
        node->prev = node;
    }
}

template<typename T, typename Alloc>
template <typename Compare>             // 必须放在第二行
void list<T, Alloc>::merge(list &sl, Compare comp)
{
    iterator dfirst = begin();
    iterator dlast = end();
    iterator sfirst = begin();
    iterator slast = end();
    // 同一个列表,不进行合并
    if (dfirst == sfirst) {
        return ;
    }
    while (dfirst != dlast && sfirst != slast) {
        if (comp(*dfirst, *sfirst)) {
            ++dfirst;
        }
        else {
            iterator next = sfirst;
            transfer(dfirst, sfirst, ++next);
            sfirst = next;
        }
    }
    if (sfirst != slast) {
        transfer(dlast, sfirst, slast);
    }
}

template<typename T, typename Alloc>
void list<T, Alloc>::remove(const_reference value)
{
    iterator it = begin();
    while (it != end()) {
        iterator curr = it;
        ++it;
        if (*curr == value) {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
            Alloc().destroy(&curr.pNode->data);
            NodeAlloc().deallocate(curr.pNode, 1);
        }
    }
}

template<typename T, typename Alloc>
template<typename Predicate>
void list<T, Alloc>::remove_if(Predicate pred)
{
    iterator it = begin();
    while (it != end()) {
        iterator curr = it;
        ++it;
        if (pred(*curr)) {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
            Alloc().destroy(&curr.pNode->data);
            NodeAlloc().deallocate(curr.pNode, 1);
        }
    }
}

template<typename T, typename Alloc>
template <typename Compare>
void list<T, Alloc>::sort()
{

}

template<typename T, typename Alloc>
void list<T, Alloc>::swap(list& l)
{
    ListNode *node = l.endNode;
    l.endNode = endNode;
    endNode = node;
}

template<typename T, typename Alloc>
template <class BinaryPredicate>
void list<T, Alloc>::unique(BinaryPredicate binaryPred)
{
    iterator prev = begin();
    iterator curr = prev;
    ++curr;
    while (curr != end()) {
        iterator del = curr++;
        if (binaryPred(*prev, *del)) {
            erase(del);
        }
    }
}

}


#endif //SIMPLESTL_LIST_H
