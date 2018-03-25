#include <iostream>
#include <list>
#include <string>
#include "list.h"
#include "vector.h"

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
    sl.back() = "...";
    cout << "sl = " << sl << endl;
    cout << "sl.back() = " << sl.back() << endl;
    cout << "sl.front() = " << sl.front() << endl;
}

void testMove()
{
    cout << "----------testMove----------" << endl;
    sstl::list<int> l1({1, 2, 3, 4, 5});
    cout << "l1" << l1 << endl;
    l1.transfer(l1.begin(), --l1.end(), l1.end());
    cout << "l1" << l1 << endl;
    l1.pop_back();
    l1.pop_back();
    cout << "l1" << l1 << endl;
    l1.transfer(l1.begin(), --l1.end(), l1.end());
    cout << "l1" << l1 << endl;

    sstl::list<int> l2;
    cout << "l1" << l1 << endl;
    cout << "l2" << l2 << endl;
    l2.transfer(l2.begin(), --l1.end(), l1.end());
    cout << "l1" << l1 << endl;
    cout << "l2" << l2 << endl;
    l2.transfer(l2.begin(), l1.begin(), l1.end());
    cout << "l1" << l1 << endl;
    cout << "l2" << l2 << endl;
    l2.remove(2);
    cout << "l2" << l2 << endl;
    l2 = sstl::list<int>({1, 2, 2, 3, 3, 4, 4, 5, 5});
    cout << "l2" << l2 << endl;
    l2.remove(3);
    cout << "l2" << l2 << endl;
    l2.remove_if([](int x){return x>=4;});
    cout << "l2" << l2 << endl;

    sstl::list<int> l3({2, 4, 5});
    cout << "l3" << l3 << endl;
    l3.merge(l2, [](int x, int y){return x<y;});
    cout << "l2" << l2 << endl;
    cout << "l3" << l3 << endl;
    l2.swap(l3);
    cout << "l2" << l2 << endl;
    cout << "l3" << l3 << endl;
    l2.unique();
    cout << "l2" << l2 << endl;

    sstl::list<int> l4({4, 1, 9, 7, 1, 2, 0, 7});
    l4.sort();
    cout << "l4" << l4 << endl;
    l4.sort([](int x, int y){return x>y;});
    cout << "l4" << l4 << endl;
}

void testList()
{
    testConstruct();
    testIterator();
    testInsert();
    testMove();
}

void testVector()
{
    sstl::vector<int> v;
    v.push_back(1);
    v.insert(v.begin(), 0);
    v.insert(v.begin(), -1);
    v.insert(v.begin(), -2);
    v.insert(v.begin(), -3);
    v.insert(v.begin(), -4);
    v.insert(v.begin(), -5);
    v.insert(v.begin(), -6);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.insert(v.end(), 6);
    list<int> l({0, 0, 0, 0, 0});
    v.insert(v.begin()+6, l.begin(), l.end());
    cout << v << endl;
    v.erase(v.begin() + 6);
    cout << v << endl;
}

int main()
{
//    testList();
    testVector();
    return 0;
}