#include "BinarySearchTree.h"
#include "AvlTree.h"
#include <iostream>
using namespace std;


void binary()
{
    BinarySearchTree<int> tree;

    tree.insert(4);
    tree.insert(3);
    tree.insert(1);
    tree.insert(6);
    tree.insert(10);
    tree.insert(5);
    tree.insert(7);
    tree.insert(5);
    cout << tree.toString() << endl;
    cout << tree.contains(5) << endl;
    tree.remove(6);
    tree.remove(5);
    cout << tree.toString() << endl;
    cout << tree.find(7)->value << endl;

    BinarySearchTree<int> tree2 = tree;
    cout << tree2.toString() << endl;
    BinarySearchTree<int> tree3;
    tree3 = tree2;
    cout << tree3.toString() << endl;
}

void avl()
{
    AvlTree<int> tree;
    tree.insert(3);
    tree.insert(5);
    tree.insert(15);
    tree.insert(1);
    tree.insert(6);
    tree.insert(0);
    tree.insert(23);
    tree.insert(18);
}

int main()
{
    binary();
    avl();
    return 0;
}