#include <iostream>
#include <list>
#include <string>
#include "list.h"
using namespace std;

int main() {
    sstl::list<int> l({1, 2});
    cout << l.empty() << endl;
    cout << l.size() << endl;
    if (l.begin() == l.end()) {
        cout << "empty" << endl;
    }
    l.insert(l.begin(), 0);

    auto it = l.begin();
    while (it != l.end()) {
        cout << *it << endl;
        ++it;
    }
    l.clear();
    cout << l.size() << endl;
    l.insert(l.begin(), 0);
    l.insert(l.end(), 1);
    it = l.begin();
    while (it != l.end()) {
        cout << *it << endl;
        ++it;
    }

    sstl::list<int> ll(l.begin(), l.end());
    it = ll.begin();
    while (it != ll.end()) {
        cout << *it << endl;
        ++it;
    }

    int arr[5] = {10, 20, 30, 40, 50};
    sstl::list<int> lll(begin(arr), end(arr));
    it = lll.begin();
    while (it != lll.end()) {
        cout << *it << endl;
        ++it;
    }

    std::list<int> sl = {100, 200, 300};
    sstl::list<int> llll(sl.cbegin(), sl.cend());
    it = llll.begin();
    while (it != llll.end()) {
        cout << *it << endl;
        ++it;
    }

    sstl::list<int> lllll(3);
    auto dit = lllll.begin();
    while (dit != lllll.end()) {
        cout << *dit << endl;
        ++dit;
    }

    sstl::list<int> il = llll;
    auto iit = il.begin();
    while (iit != il.end()) {
        cout << *iit << endl;
        ++iit;
    }

    il = lllll;
    iit = il.insert(il.begin(), begin(arr), end(arr));
    cout << *iit << endl;
    iit = il.begin();
    il.erase(++iit);
    iit = il.begin();
    while (iit != il.end()) {
        cout << *iit << endl;
        ++iit;
    }

    iit = il.begin();
    auto iiit = ++iit;
    ++iit;
    il.erase(iit, iiit);
    iit = il.begin();
    while (iit != il.end()) {
        cout << *iit << endl;
        ++iit;
    }

    return 0;
}