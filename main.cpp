#include <iostream>
#include <list>
#include <string>
#include "list.h"
using namespace std;

void testConstruct()
{
    cout << "----------testConstruct----------" << endl;
    sstl::list<int> l({1, 2,3});
    cout << "l = " << l << endl;

    sstl::list<int> l1;
    cout << "l1 = " << l1 << endl;

    sstl::list<int> l2(3);
    cout << "l2 = " << l2 << endl;

    sstl::list<string> l3(10, "hello");
    cout << "l3 = " << l3 << endl;

    sstl::list<string> l4(l3.begin(), l3.end());
    cout << "l4 = " << l4 << endl;

    sstl::list<string> l5(l4);
    cout << "l5 = " << l5 << endl;

    sstl::list<string> l6(3, "hi");
    l6 = l4;
    cout << "l6 = " << l6 << endl;

    cout << "l6.size() = " << l6.size() << endl;
    cout << "l6.max_size() = " << l6.max_size() << endl;
    cout << "l6.empty() = " << l6.empty() << endl;

    l6.clear();
    cout << "l6.clear()" << endl;
    cout << "l6.size() = " << l6.size() << endl;
    cout << "l6.max_size() = " << l6.max_size() << endl;
    cout << "l6.empty() = " << l6.empty() << endl;
}

void testIterator()
{
    cout << "----------testIterator----------" << endl;
    sstl::list<int> l({1, 2, 3, 4, 5});
    auto it = l.begin();
    while (it != l.end()) {
        cout << *it++ << endl;
    }
}

void testInsert()
{
    cout << "----------testInsert----------" << endl;
    sstl::list<int> l({1, 2, 3, 4, 5});
    cout << "l = " << l << endl;
    auto it = l.begin();
    it = l.insert(it, 0);
    cout << "l = " << l << endl;
    ++it; ++it;
    l.insert(it, 0);
    cout << "l = " << l << endl;
    l.insert(l.end(), 6);
    cout << "l = " << l << endl;

    sstl::list<string> sl(1, "world");
    cout << "sl = " << sl << endl;
    sl.insert(sl.begin(), 1, "hello");
    cout << "sl = " << sl << endl;
    std::list<string> stdl(2, "!");
    sl.insert(sl.end(), stdl.begin(), stdl.end());
    cout << "sl = " << sl << endl;
    sl.pop_back();
    cout << "sl = " << sl << endl;
    sl.push_back("!");
    cout << "sl = " << sl << endl;
    sl.push_front("hi");
    cout << "sl = " << sl << endl;
    sl.erase(sl.begin());
    cout << "sl = " << sl << endl;
    sl.erase(--sl.end());
    cout << "sl = " << sl << endl;
    sl.insert(++sl.begin(), 2, "test");
    cout << "sl = " << sl << endl;
    auto sit = ++sl.begin();
    auto eit = sit; ++eit; ++eit;
    sl.erase(sit, eit);
    cout << "sl = " << sl << endl;
}

int main()
{
    testConstruct();
    testIterator();
    testInsert();
    return 0;
}