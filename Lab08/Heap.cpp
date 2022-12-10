/*
 * IMPLEMENTED BY: ASHWIN ABRAHAM
 */

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef HEAP_H
#include "Heap.h"
#endif

template <typename T>
void Heap<T>::insert(T obj)
{
    static int num = 0;
    ++num;
    // insert your code here
    ++size;
    if(root == nullptr)
    {
        root = new TreeNode<T>(obj);
        last = root;
        return;
    }
    for(TreeNode<T>* next = last; ; next = next->parent)
    {
        if(next->parent == nullptr)
        {
            while(next->left != nullptr) next = next->left;
            next->left = new TreeNode<T>(obj);
            next->left->parent = next;
            last = next->left;
            break;
        }
        if(next->parent->left == next)
        {
            if(next->parent->right == nullptr)
            {
                next->parent->right = new TreeNode<T>(obj);
                next->parent->right->parent = next->parent;
                last = next->parent->right;
            }
            else
            {
                next = next->parent->right;
                while(next->left != nullptr) next = next->left;
                next->left = new TreeNode<T>(obj);
                next->left->parent = next;
                last = next->left;
            }
            break;
        }
    }
    for(TreeNode<T>* ptr = last; ptr->parent != nullptr; ptr = ptr->parent)
    {
        if(ptr->parent->object < ptr->object)
        {
            T temp = ptr->object;
            ptr->object = ptr->parent->object;
            ptr->parent->object = temp;
        }
    }
}

template <typename T>
void heapify(TreeNode<T>* root)
{
    if(root->right == nullptr)
    {
        if(root->left == nullptr) return;
        if(root->object < root->left->object)
        {
            T temp = root->object;
            root->object = root->left->object;
            root->left->object = temp;
        }
        return;
    }
    if(root->left->object < root->right->object)
    {
        if(root->object < root->right->object)
        {
            T temp = root->object;
            root->object = root->right->object;
            root->right->object = temp;
            heapify(root->right);
        }
    }
    else
    {
        if(root->object < root->left->object)
        {
            T temp = root->object;
            root->object = root->left->object;
            root->left->object = temp;
            heapify(root->left);
        }
    }
}

template <typename T>
void Heap<T>::delMax()
{
    if(size == 0) return;
    --size;
    // insert your code here
    if(last->parent == nullptr)
    {
        delete last;
        root = nullptr;
        last = nullptr;
        return;
    }
    T temp = root->object;
    root->object = last->object;
    last->object = temp;
    TreeNode<T>* ptr = last;
    for(; ptr->parent != nullptr && ptr->parent->left == ptr; ptr = ptr->parent);
    if(ptr->parent == nullptr)
    {
        for(; ptr->right != nullptr; ptr = ptr->right);
        if(last->parent->left == last) last->parent->left = nullptr;
        else last->parent->right = nullptr;
        delete last;
        last = ptr;
    }
    else
    {
        ptr = ptr->parent->left;
        for(; ptr->right != nullptr; ptr = ptr->right);
        if(last->parent->left == last) last->parent->left = nullptr;
        else last->parent->right = nullptr;
        delete last;
        last = ptr;
    }
    heapify(root);
    return;
}

template <typename T>
void schneider_print(TreeNode<T>* root, string prefix = "", bool isLeft=false)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->object << endl;
        // enter the next tree level - left and right branch
        printBST(root->left, prefix + (isLeft ? "│   " : "    "), true);
        printBST(root->right, prefix + (isLeft ? "│   " : "    "), false);
    }
}

template <typename T>
void Heap<T>::printHeap(TreeNode<T> *node)
{

    // insert your code here
    schneider_print(node);
    return;
}
