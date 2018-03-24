//
// Created by chenchukun on 17/11/21.
//

#ifndef SIMPLESTL_VECTOR_H
#define SIMPLESTL_VECTOR_H

#include "utility.h"
#include "reverse_iterator.h"
#include <memory>
#include <initializer_list>

NAMESPACE_START

template<typename T, typename Alloc=std::allocator<T> >
class vector
{
public:
    template<typename _T, typename _Alloc>
    friend std::ostream& operator<<(std::ostream &out, const vector<_T, _Alloc> &v);

    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef vector self;
    typedef Alloc allocator_type;
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;

    typedef T* iterator;
    typedef const T* const_iterator;
    typedef reverse_iterator<const_iterator> const_reverse_iterator;
    typedef reverse_iterator<iterator> reverse_iterator;

    vector():start(NULL),finish(NULL), endOfStorage(NULL) {}
    vector(size_type n, const_reference value);
    vector(const std::initializer_list<T> &inil);
    template<typename Iter>
    vector(Iter first, Iter last);
    vector(const self &right);

    ~vector();

    self& operator=(const self &right);

    reference operator[](size_type index) {
        return *(start + index);
    }

    const_reference operator[](size_type index) const {
        return *(start + index);
    }

    void swap(self &right) {
        std::swap(start, right.start);
        std::swap(finish, right.finish);
        std::swap(endOfStorage, right.endOfStorage);
    }

    size_type size() const {
        return finish - start;
    }

    bool empty() const {
        return finish==start;
    }

    size_type capacity() const {
        return endOfStorage - start;
    }

    void push_back(const_reference value);

    void insert(iterator it, const_reference value);

    template<typename Iter>
    void insert(iterator it, Iter first, Iter last);

    reference front() {
        return *start;
    }

    const_reference front() const {
        return *start;
    }

    reference back() {
        return *(finish -1);
    }

    const_reference back() const {
        return *(finish -1);
    }

    pointer begin() {
        return start;
    }

    const_pointer begin() const {
        return start;
    }

    pointer end() {
        return finish;
    }

    const_pointer end() const {
        return finish;
    }

private:
    void move(iterator first, iterator last, iterator dst);

private:
    pointer start;
    pointer finish;
    pointer endOfStorage;
};

template<typename T, typename Alloc>
vector<T, Alloc>::vector(size_type n, const_reference value)
{
    start = Alloc().allocate(n);
    finish = start + n;
    endOfStorage = finish;
    for (size_type i=0; i<n; ++i) {
        Alloc().construct(start+i, value);
    }
}

template<typename T, typename Alloc>
vector<T, Alloc>::vector(const std::initializer_list<T> &inil)
{
    start = Alloc().allocate(inil.size());
    finish = start + inil.size();
    endOfStorage = finish;
    size_type index = 0;
    for (auto item : inil) {
        Alloc().construct(start+(index++), item);
    }
}

template<typename T, typename Alloc>
vector<T, Alloc>::~vector()
{
    for (size_type i=0; i<size(); ++i) {
        Alloc().destroy(start+i);
    }
    Alloc().deallocate(start, endOfStorage-start);
}

template<typename T, typename Alloc>
template<typename Iter>
vector<T, Alloc>::vector(Iter first, Iter last)
{
    size_type n = 0;
    Iter _first = first;
    while (_first != last) {
        ++_first;
        ++n;
    }
    start = Alloc().allocate(n);
    finish = start + n;
    _first = first;
    size_type index = 0;
    while (_first != last) {
        Alloc().construct(start + (index++), *_first);
        ++_first;
    }
}

template<typename T, typename Alloc>
vector<T, Alloc>::vector(const self &right)
{
    start = Alloc().allocate(right.size());
    for (int i=0; i<right.size(); ++i) {
        Alloc().construct(start+i, *(right.start+i));
    }
}

template<typename T, typename Alloc>
typename vector<T, Alloc>::self& vector<T, Alloc>::operator=(const self &right)
{
    pointer pTmp = Alloc().allocate(right.size());
    for (size_type i=0; i<right.size(); ++i) {
        Alloc().construct(pTmp+i, *(right.start+i));
    }
    for (size_type i=0; i<size(); ++i) {
        Alloc().destroy(start+i);
    }
    Alloc().deallocate(start, endOfStorage-start);
    start = pTmp;
}

template<typename T, typename Alloc>
std::ostream& operator<<(std::ostream &out, const vector<T, Alloc> &v)
{
    out << "(";
    if (!v.empty()) {
        out << v[0];
    }
    for (size_t i=1; i<v.size(); ++i) {
        out << ", " << v[i];
    }
    out << ")";
    return out;
}

template<typename T, typename Alloc>
void vector<T, Alloc>::push_back(const_reference value)
{
    insert(end(), value);
}

template<typename T, typename Alloc>
void vector<T, Alloc>::insert(iterator it, const_reference value)
{
    insert(it, &value, (&value) + 1);
}

template<typename T, typename Alloc>
template<typename Iter>
void vector<T, Alloc>::insert(iterator it, Iter first, Iter last)
{
    size_t n = 0;
    Iter tmpIt = first;
    while (tmpIt != last) {
        ++tmpIt;
        ++n;
    }
    if (endOfStorage - finish >= n) {
        // 直接插入
        move(it, end(), it + n);
        while (first != last) {
            *it++ = *first++;
        }
        finish += n;
    }
    else {
        size_t newCap = capacity() * 2;
        pointer newMem = Alloc().allocate(newCap);
        move(begin(), it, newMem);
        pointer insIt = newMem + (it - begin());
        while (first != last) {
            *insIt++ = *first++;
        }
        move(it, end(), insIt);
        finish = newMem + size() + n;
        start = newMem;
        endOfStorage = start + newCap;
    }
}

template<typename T, typename Alloc>
void vector<T, Alloc>::move(iterator first, iterator last, iterator dst)
{
    while (first != last) {
        *dst++ = *first++;
    }
}

NAMESPACE_END

#endif //SIMPLESTL_VECTOR_H
