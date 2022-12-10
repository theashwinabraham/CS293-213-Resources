/*
 * IMPLEMENTED BY: ASHWIN ABRAHAM
 */

#ifndef HEAP_H
#define HEAP_H

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

using namespace std;

template <typename T>
class TreeNode
{
public:
    T object;
    TreeNode<T> *left;
    TreeNode<T> *right;
    TreeNode<T> *parent;

    TreeNode(T initObj)
    {
        object = initObj;
        left = right = parent = nullptr;
    }
    ~TreeNode() { ; }
};

template <typename T>
void recursiveDelete(TreeNode<T>* root)
{
    if(root == nullptr) return;
    recursiveDelete(root->left);
    recursiveDelete(root->right);
    delete root;
}

template <typename T>
class Heap
{
    TreeNode<T> *root;
    int size;
    TreeNode<T> *last;
public:
    Heap() { root = nullptr; size = 0; last = nullptr; }
    ~Heap() { recursiveDelete(root); }

    void insert(T obj);
    void delMax();
    T getMax()
    {
        return root->object; // insert your own code here if needed
    }
    void printHeap(TreeNode<T> *node);
    //  void displayAboveThresh(int thresh);
};

#endif
