//
// Created by chenchukun on 17/11/21.
//

#ifndef SIMPLESTL_VECTOR_H
#define SIMPLESTL_VECTOR_H

#include "utility.h"
#include <memory>

NAMESPACE_START

template<typename T, Alloc=std::allocator<T> >
class vector
{
public:
    typedef T value_type;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef T& reference;
    typedef const T& const_reference;
    typedef vector self;

private:
    pointer start;
    pointer finish;
    pointer endOfStorage;
};

NAMESPACE_END

#endif //SIMPLESTL_VECTOR_H
