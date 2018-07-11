#ifndef SIMPLESTL_BINARYSEARCHTREE_HPP
#define SIMPLESTL_BINARYSEARCHTREE_HPP

#include <functional>
#include <string>
#include <sstream>
#include <queue>

template<typename T, typename C = std::less<T>>
class BinarySearchTree
{
public:
    struct BinaryNode
    {
        T value;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode(const T &v, BinaryNode *l=NULL, BinaryNode *r=NULL)
                : value(v), left(l), right(r)
        {
        }
    };

    BinarySearchTree()
        : root_(NULL)
    {
    }

    ~BinarySearchTree() {
        makeEmpty(root_);
    }

    BinarySearchTree(const BinarySearchTree &rhs);

    BinarySearchTree& operator=(const BinarySearchTree &rhs);

    BinaryNode* insert(const T &value);

    bool empty() const {
        return root_ == NULL;
    }

    void clear() {
        makeEmpty(root_);
    }

    BinaryNode* find(const T &value) {
        return find(value, root_);
    }

    const BinaryNode* find(const T &value) const {
        return find(value, root_);
    }

    bool contains(const T &value) const {
        return find(value) != NULL;
    }

    bool contains(const T &value) {
        return find(value) != NULL;
    }

    std::string toString() const;

    T findMax() const {
        return T();
    }

    T findMin() const {
        return T();
    }

    void remove(const T &value) {
        remove(value, root_);
    }

private:
    void makeEmpty(BinaryNode *&pNode);

    BinaryNode* insert(const T &value, BinaryNode *&pRoot);

    BinaryNode* find(const T &value, BinaryNode *pRoot);

    const BinaryNode* find(const T &value, BinaryNode *pRoot) const;

    BinaryNode* findMax(BinaryNode *pRoot) const;

    BinaryNode* findMin(BinaryNode *pRoot) const;

    void remove(const T &value, BinaryNode *&pRoot);

    BinaryNode* clone(BinaryNode *pRoot) const;

private:
    BinaryNode *root_;
};


template <typename T, typename C>
BinarySearchTree<T, C>::BinarySearchTree(const BinarySearchTree &rhs)
{
    root_ = clone(rhs.root_);
}

template <typename T, typename C>
BinarySearchTree<T, C>& BinarySearchTree<T, C>::operator=(const BinarySearchTree &rhs)
{
    BinaryNode *pRoot = clone(rhs.root_);
    makeEmpty(root_);
    root_ = pRoot;
    return *this;
}

template <typename T, typename C>
typename BinarySearchTree<T, C>::BinaryNode* BinarySearchTree<T, C>::clone(BinaryNode *pRoot) const
{
    BinaryNode *pNode = NULL;
    if (pRoot) {
        pNode = new BinaryNode(pRoot->value, clone(pRoot->left), clone(pRoot->right));
    }
    return pNode;
}

template<typename T, typename C>
void BinarySearchTree<T, C>::remove(const T &value, BinaryNode *&pRoot)
{
    if (pRoot) {
        if (C()(value, pRoot->value)) {
            remove(value, pRoot->left);
        }
        else if (C()(pRoot->value, value)) {
            remove(value, pRoot->right);
        }
        else if (pRoot->left && pRoot->right){
            pRoot->value = findMin(pRoot->right)->value;
            remove(pRoot->value, pRoot->right);
        }
        else {
            BinaryNode *pNode = pRoot;
            pRoot = (pRoot->left)? pRoot->left: pRoot->right;
            delete pNode;
        }
    }
}

template<typename T, typename C>
const typename BinarySearchTree<T, C>::BinaryNode* BinarySearchTree<T, C>::find(const T &value, BinaryNode *pRoot) const
{
    BinaryNode *pNode = NULL;
    if (pRoot) {
        if (C()(value, pRoot->value)) {
            pNode = find(value, pRoot->left);
        }
        else if (C()(pRoot->value, value)) {
            pNode = find(value, pRoot->right);
        }
        else {
            pNode = pRoot;
        }
    }
    return pNode;
}

template<typename T, typename C>
typename BinarySearchTree<T, C>::BinaryNode* BinarySearchTree<T, C>::find(const T &value, BinaryNode *pRoot)
{
    BinaryNode *pNode = NULL;
    if (pRoot) {
        if (C()(value, pRoot->value)) {
            pNode = find(value, pRoot->left);
        }
        else if (C()(pRoot->value, value)) {
            pNode = find(value, pRoot->right);
        }
        else {
            pNode = pRoot;
        }
    }
    return pNode;
}

template<typename T, typename C>
typename BinarySearchTree<T, C>::BinaryNode* BinarySearchTree<T, C>::findMax(BinaryNode *pRoot) const
{
    BinaryNode *pNode = NULL;
    if (pRoot) {
        if (pRoot->right) {
            pNode = findMax(pRoot->right);
        }
        else {
            pNode = pRoot;
        }
    }
    return pNode;
}

template<typename T, typename C>
typename BinarySearchTree<T, C>::BinaryNode* BinarySearchTree<T, C>::findMin(BinaryNode *pRoot) const
{
    BinaryNode *pNode = NULL;
    if (pRoot) {
        if (pRoot->left) {
            pNode = findMin(pRoot->left);
        }
        else {
            pNode = pRoot;
        }
    }
    return pNode;
}

template<typename T, typename C>
void BinarySearchTree<T, C>::makeEmpty(BinaryNode *&pNode)
{
    if (pNode != NULL) {
        makeEmpty(pNode->left);
        makeEmpty(pNode->right);
        delete pNode;
        pNode = NULL;
    }
}

template<typename T, typename C>
typename BinarySearchTree<T, C>::BinaryNode* BinarySearchTree<T, C>::insert(const T &value)
{
    return insert(value, root_);
}

template<typename T, typename C>
typename BinarySearchTree<T, C>::BinaryNode* BinarySearchTree<T, C>::insert(const T &value, BinaryNode *&pRoot)
{
    if (pRoot == NULL) {
        pRoot = new BinaryNode(value);
        return pRoot;
    }
    if (C()(value, pRoot->value)) {
        return insert(value, pRoot->left);
    }
    else {
        return insert(value, pRoot->right);
    }
}

template<typename T, typename C>
std::string BinarySearchTree<T, C>::toString() const
{
    std::stringstream os;
    if (root_ != NULL)
    {
        std::queue<BinaryNode*> que;
        que.push(root_);
        while (!que.empty()) {
            BinaryNode *pNode = que.front();
            que.pop();
            os << pNode->value << " ";
            if (pNode->left) {
                que.push(pNode->left);
            }
            if (pNode->right) {
                que.push(pNode->right);
            }
        }
    }
    return os.str();
}


#endif //SIMPLESTL_BINARYSEARCHTREE_HPP
