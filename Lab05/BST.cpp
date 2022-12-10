#ifndef BST_H
#include "BST.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif
#include <cassert>

bool BSTisLeftChild(TreeNode* tr)
{
    assert(tr != nullptr);
    assert(tr->parent != nullptr);
    return tr->parent->left == tr;
}

// updates heights along a path from a node to root
// node should not be null
// children of node should be null or have the correct height
void BST_update_heights(TreeNode* node)
{
    for(TreeNode* curr = node; curr != nullptr; curr = curr->parent)
    {
        if(curr->left == nullptr)
        {
            if(curr->right == nullptr)
            {
                curr->height = 0;
            }
            else
            {
                curr->height = 1 + curr->right->height;
            }
        }
        else
        {
            if(curr->right == nullptr)
            {
                curr->height = 1 + curr->left->height;
            }
            else
            {
                curr->height = 1 + ((curr->left->height < curr->right->height) ? curr->right->height : curr->left->height);
            }
        }
    }
}

// Returns true on successful insertion in BST. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the BST

bool BST::insert(int jrnyCode, int price)
{
    // Implement insertion in BST

    // You MUST use only BSTLessThan to compare two journey codes.  You
    // can create a new node containing the journey code to be inserted
    // and invoke BSTLessThan on the current node in the tree that you
    // are inspecting and the new node to do your comparison.

    // REMEMBER to update the heights of appropriate nodes in the tree
    // after an insertion.

    // We use "return true" below to enable compilation.  Change this as you
    // see fit.
    TreeNode temp(jrnyCode, price);
    TreeNode* parent = nullptr;
    bool is_left = false;
    for(TreeNode* curr = root; ;)
    {
        if(curr == nullptr)
        {
            curr = new TreeNode(jrnyCode, price);
            curr->parent = parent;
            if(parent != nullptr)
            {
                if(is_left)
                {
                    parent->left = curr;
                }
                else
                {
                    parent->right = curr;
                }
            }
            else
            {
                root = curr;
            }

            BST_update_heights(curr);

            return true;
        }
        else if(BSTLessThan(&temp, curr))
        {
            is_left = true;
            parent = curr;
            curr = curr->left;
        }
        else if(BSTLessThan(curr, &temp))
        {
            is_left = false;
            parent = curr;
            curr = curr->right;
        }
        else
        {
            return false;
        }
    }
}

// Returns the price on finding an element in the BST that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the BST

int BST::find(int jrnyCode)
{
    // Implement find in BST

    // You MUST use only BSTLessThan to compare two journey codes.  You
    // can create a new node containing the journey code to be searched
    // (along with some arbitrary price) and invoke BSTLessThan on the
    // current node in the tree that you are inspecting and the new node
    // to do your comparison.

    // We use "return -1" below to enable compilation.  Change this as you
    // see fit.
    TreeNode temp(jrnyCode, -1);
    for(TreeNode* curr = root; ;)
    {
        if(curr == nullptr)
        {
            break;
        }
        else if(BSTLessThan(&temp, curr))
        {
            curr = curr->left;
        }
        else if(BSTLessThan(curr, &temp))
        {
            curr = curr->right;
        }
        else
        {
            return curr->getPrice();
        }
    }
    return -1;
}

// =====================================================
// OPTIONAL: Implement "remove" only for bonus marks
// =====================================================


void remove_node(TreeNode* node, TreeNode** root_ptr)
{
    if(node->left == nullptr && node->right == nullptr)
    {
        if(node->parent == nullptr)
        {
            delete node;
            *root_ptr = nullptr;
        }
        else
        {
            TreeNode* pr = node->parent;
            if(BSTisLeftChild(node))
            {
                pr->left = nullptr;
            }
            else
            {
                pr->right = nullptr;
            }
            delete node;
            BST_update_heights(pr);
        }
    }
    else if(node->left == nullptr)
    {
        if(node->parent == nullptr)
        {
            *root_ptr = node->right;
            delete node;
        }
        else
        {
            /*TreeNode* tr = node->right;
            for(; tr->left != nullptr; tr = tr->left);
            int h = node->height;
            TreeNode* pr = node->parent;
            TreeNode* l = node->left;
            TreeNode* r = node->right;*/
            TreeNode* pr = node->parent;
            if(BSTisLeftChild(node))
            {
                pr->left = node->right;
            }
            else
            {
                pr->right = node->right;
            }

            delete node;

            BST_update_heights(pr);
        }
    }
    else if(node->right == nullptr)
    {
        if(node->parent == nullptr)
        {
            *root_ptr = node->left;
            delete node;
        }
        else
        {
            TreeNode* pr = node->parent;
            if(BSTisLeftChild(node))
            {
                pr->left = node->left;
            }
            else
            {
                pr->right = node->left;
            }

            delete node;

            BST_update_heights(pr);
        }
    }
    else
    {
        TreeNode* tr = node->left;
        for(; tr->right != nullptr; tr = tr->right);
        int h = node->height;
        TreeNode* pr = node->parent;
        TreeNode* l = node->left;
        TreeNode* r = node->right;
        *node = *tr;
        node->parent = pr;
        node->left = l;
        node->right = r;
        node->height = h;

        TreeNode* trp = tr->parent;
        if(BSTisLeftChild(tr))
        {
            trp->left = tr->left;
        }
        else
        {
            trp->right = tr->left;
        }

        delete tr;

        BST_update_heights(tr);
    }
}

// Returns true on successful deletion of the entry in BST with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the BST have the same journey
// code, and journey code is the key for insertion and finding in the BST.

bool BST::remove(int jrnyCode)
{
    // Implement deletion in BST

    // You MUST use only BSTLessThan to compare two journey codes.  You
    // can create a new node containing the journey code to be searched
    // (along with some arbitrary price) and invoke BSTLessThan on the
    // current node in the tree that you are inspecting and the new node
    // to do your comparison.

    // REMEMBER to update the height of appropriate nodes in the tree
    // after a successful deletion.

    // We use "return true" below to enable compilation.  Change this as you
    // see fit.
    TreeNode temp(jrnyCode, -1);
    for(TreeNode* curr = root; ;)
    {
        if(curr == nullptr)
        {
            return false;
        }
        else if(BSTLessThan(&temp, curr))
        {
            curr = curr->left;
        }
        else if(BSTLessThan(curr, &temp))
        {
            curr = curr->right;
        }
        else
        {
            remove_node(curr, &root);
            break;
        }
    }
    return true;
}
