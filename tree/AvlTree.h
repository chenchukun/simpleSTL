#ifndef SIMPLESTL_AVLTREE_H
#define SIMPLESTL_AVLTREE_H

#include <functional>
#include <string>
#include <iostream>
#include <queue>

template<typename T, typename C = std::less<T>>
class AvlTree
{
public:
    struct AvlNode {
        AvlNode(const T &v, int h=0, AvlNode *l=NULL, AvlNode *r=NULL)
            : value(v), height(h), left(l), right(r)
        {
        }

        T value;
        AvlNode *left;
        AvlNode *right;
        int height;
    };

    AvlTree(): root_(NULL) {}

    ~AvlTree() {
        makeEmpty(root_);
    }

    AvlNode* insert(const T &value) {
        return insert(root_, value);
    }

    AvlNode* find(const T &value) const {
        return find(value, root_);
    }

    AvlNode* find(const T &value) {
        return find(value, root_);
    }

    T findMax() const {
        return findMax(root_)->value;
    }

    T findMin() const {
        return findMin(root_)->value;
    }

    bool empty() const {
        return root_ == NULL;
    }

    void clear() {
        makeEmpty(root_);
    }

    bool contains(const T &value) const {
        return find(value) != NULL;
    }

    bool contains(const T &value) {
        return find(value) != NULL;
    }

    void remove(const T &value) {
        remove(value, root_);
    }

    std::string toString() const;

private:
    void makeEmpty(AvlNode *&pRoot);

    void leftRotate(AvlNode *&pNode);

    void rightRotate(AvlNode *&pNode);

    AvlNode* insert(AvlNode *&pRoot, const T &value);

    AvlNode* find(const T &value, AvlNode *pRoot);

    AvlNode* find(const T &value, AvlNode *pRoot) const;

    AvlNode* findMax(AvlNode *pRoot) const;

    AvlNode* findMin(AvlNode *pRoot) const;

    void remove(const T &value, AvlNode *&pRoot);

    int getHeight(AvlNode *pNode) {
        return pNode == NULL? -1: pNode->height;
    }

private:
    AvlNode *root_;
};

template<typename T, typename C>
void AvlTree<T, C>::makeEmpty(AvlNode *&pRoot) {
    if (pRoot != NULL) {
        makeEmpty(pRoot->left);
        makeEmpty(pRoot->right);
        delete pRoot;
        pRoot = NULL;
    }
}

template<typename T, typename C>
void AvlTree<T, C>::leftRotate(AvlNode *&pNode)
{
    AvlNode *right = pNode->right;
    pNode->right = right->left;
    right->left = pNode;
    pNode = right;
    pNode->height = getHeight(pNode->left) > getHeight(pNode->right)?
        getHeight(pNode->left) + 1: getHeight(pNode->right) + 1;
    pNode->left->height = getHeight(pNode->left->left) > getHeight(pNode->left->right)?
        getHeight(pNode->left->left) + 1: getHeight(pNode->left->right) + 1;
}

template<typename T, typename C>
void AvlTree<T, C>::rightRotate(AvlNode *&pNode)
{
    AvlNode *left = pNode->left;
    pNode->left = left->right;
    left->right = pNode;
    pNode = left;
    pNode->height = getHeight(pNode->left) > getHeight(pNode->right)?
        getHeight(pNode->left) + 1: getHeight(pNode->right) + 1;
    pNode->right->height = getHeight(pNode->right->left) > getHeight(pNode->right->right)?
        getHeight(pNode->right->left) + 1: getHeight(pNode->right->right) + 1;
}

template<typename T, typename C>
typename AvlTree<T, C>::AvlNode* AvlTree<T, C>::insert(AvlNode *&pRoot, const T &value)
{
    if (pRoot == NULL) {
        pRoot = new AvlNode(value);
        return pRoot;
    }
    AvlNode *pNode = NULL;
    if (C()(pRoot->value, value)) {
        pNode = insert(pRoot->right, value);
    }
    else {
        pNode = insert(pRoot->left, value);
    }
    int lHeight = getHeight(pRoot->left);
    int rHeight = getHeight(pRoot->right);

    if (lHeight > rHeight && lHeight - rHeight >= 2) {
        // 右旋转
        if (getHeight(pRoot->left->left) > getHeight(pRoot->left->right)) {
            rightRotate(pRoot);
        }
        // 双旋转,先左后右
        else {
            leftRotate(pRoot->left);
            rightRotate(pRoot);
        }
    }
    else if (rHeight > lHeight && rHeight - lHeight >= 2) {
        // 左旋转
        if (getHeight(pRoot->right->right) > getHeight(pRoot->right->left)) {
            leftRotate(pRoot);
        }
        // 双旋转,先右后左
        else {
            rightRotate(pRoot->right);
            leftRotate(pRoot);
        }
    }
    pRoot->height = getHeight(pRoot->left) > getHeight(pRoot->right)?
        getHeight(pRoot->left) + 1: getHeight(pRoot->right) + 1;
    return pNode;
}

template<typename T, typename C>
std::string AvlTree<T, C>::toString() const
{
    std::stringstream os;
    if (root_ != NULL)
    {
        std::queue<AvlNode*> que;
        que.push(root_);
        while (!que.empty()) {
            AvlNode *pNode = que.front();
            que.pop();
            os << pNode->value << "(" << pNode->height << ") ";
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


template<typename T, typename C>
typename AvlTree<T, C>::AvlNode* AvlTree<T, C>::find(const T &value, AvlNode *pRoot)
{
    AvlNode *pNode = NULL;
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
typename AvlTree<T, C>::AvlNode* AvlTree<T, C>::find(const T &value, AvlNode *pRoot) const
{
    AvlNode *pNode = NULL;
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
typename AvlTree<T, C>::AvlNode* AvlTree<T, C>::findMax(AvlNode *pRoot) const
{
    if (pRoot && pRoot->right) {
        return findMax(pRoot->right);
    }
    return pRoot;
}

template<typename T, typename C>
typename AvlTree<T, C>::AvlNode* AvlTree<T, C>::findMin(AvlNode *pRoot) const
{
    if (pRoot && pRoot->left) {
        return findMin(pRoot->left);
    }
    return pRoot;
}

template<typename T, typename C>
void AvlTree<T, C>::remove(const T &value, AvlNode *&pRoot)
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
            AvlNode *pNode = pRoot;
            pRoot = (pRoot->left)? pRoot->left: pRoot->right;
            delete pNode;
        }
        if (pRoot) {
            int lHeight = getHeight(pRoot->left);
            int rHeight = getHeight(pRoot->right);
            if (lHeight > rHeight && lHeight - rHeight >= 2) {
                // 右旋转
                if (getHeight(pRoot->left->left) > getHeight(pRoot->left->right)) {
                    rightRotate(pRoot);
                }
                    // 双旋转,先左后右
                else {
                    leftRotate(pRoot->left);
                    rightRotate(pRoot);
                }
            }
            else if (rHeight > lHeight && rHeight - lHeight >= 2) {
                // 左旋转
                if (getHeight(pRoot->right->right) > getHeight(pRoot->right->left)) {
                    leftRotate(pRoot);
                }
                    // 双旋转,先右后左
                else {
                    rightRotate(pRoot->right);
                    leftRotate(pRoot);
                }
            }
            pRoot->height = getHeight(pRoot->left) > getHeight(pRoot->right) ?
               getHeight(pRoot->left) + 1 : getHeight(pRoot->right) + 1;
        }
    }
}

#endif //SIMPLESTL_AVLTREE_H
