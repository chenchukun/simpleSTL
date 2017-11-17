//
// Created by chenchukun on 17/11/11.
//

#ifndef SIMPLESTL_REVERSE_ITERATOR_H
#define SIMPLESTL_REVERSE_ITERATOR_H
#include "utility.h"

NAMESPACE_START

template<class Iterator>
class reverse_iterator
{
public:
    reverse_iterator(Iterator it): iter(it) {}

private:
    Iterator iter;
};

NAMESPACE_END


#endif //SIMPLESTL_REVERSE_ITERATOR_H
