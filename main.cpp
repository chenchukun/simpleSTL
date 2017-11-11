#include <iostream>
#include <list>
#include "list.h"
using namespace std;

int main() {
    sstl::list<int> l({1, 2});
    cout << l.empty() << endl;
    if (l.begin() == l.end()) {
        cout << "empty" << endl;
    }

    auto it = l.begin();
    while (it != l.end()) {
        cout << *it << endl;
        ++it;
    }
    return 0;
}