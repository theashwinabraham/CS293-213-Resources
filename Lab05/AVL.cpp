/*
 * IMPLEMENTED BY: ASHWIN ABRAHAM
 */

#ifndef AVL_H
#include "AVL.h"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif
#include <cassert>

bool AVLisLeftChild(TreeNode* tr)
{
    assert(tr != nullptr);
    assert(tr->parent != nullptr);
    return tr->parent->left == tr;
}

// imbalance = height of if right child was null - height of node if left child was null
// effectively, height of null is -1
int imbalance(TreeNode* n)
{
    assert(n != nullptr);
    if(n->left == nullptr && n->right == nullptr) return 0;
    if(n->left == nullptr) return -1-n->right->height;
    if(n->right == nullptr) return 1+n->left->height;
    return n->left->height - n->right->height;
}

// updates heights along a path from a node (inclusive) to point where |imbalance| > 1 (inclusive) and returns the grandchild of that point in path
// if such a point doesn't exist, it updates all the way to root (inclusive), and returns null
// after rebalancing, height of nodes above imbalanced node remains same
// node should not be null
// children of node should be null or have the correct height
TreeNode* AVL_update_heights(TreeNode* node)
{
    TreeNode* curr = node;
    TreeNode* child = nullptr;
    TreeNode* grandchild = nullptr;
    for(; curr != nullptr; grandchild = child, child = curr, curr = curr->parent)
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
        if(abs(imbalance(curr)) > 1) return grandchild; // will never be null
    }
    return nullptr;
}

// Recall from Prof. Naveen Garg's lectures how the various rotations are
// applied to restore the balance factor at all nodes of an AVL tree
// to either 0, 1 or -1, after an insert or delete.
// The correspondence between the terminology in Prof. Garg's lectures and
// our terminology in this code is as follows:
//
// Prof. Garg's lectures           Our code
// ---------------------           --------
//   x                             currNode
//   y                             parentNode
//   z                             grandParentNode
//
// Recall also that z (grandParentNode) is the lowest node in the path from
// the root to the inserted node or to the deleted node (as the case may be)
// where the balance factor has either become < -1 or > 1.
// To find what x (currNode) and y (parentNode) should be, you need to
// recall Prof. Garg's lectures.
// These are slightly differently defined when inserting nodes and when
// deleting nodes

bool AVLTree::rotateLeftLeft(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
    // Going back to Prof. Naveen Garg's lecture, x is *currNode,
    // y is *parentNode and z is *grandParentNode

    // Moreover, currNode is the left child of parentNode, and
    // parentNode is the left child of grandParentNode
    // That's why we are doing a rotateLeftLeft

    TreeNode *greatGrandParentNode = grandParentNode->parent;

    // First find if grandParentNode is the left or right child of
    // greatGrandParentNode

    bool isGPLeftChild;
    if(greatGrandParentNode != nullptr)
    {
        if (greatGrandParentNode->left == grandParentNode)
        {
            isGPLeftChild = true;
        }
        else if (greatGrandParentNode->right == grandParentNode)
        {
            isGPLeftChild = false;
        }
        else
        {
            cerr << "Unexpected condition encountered!" << endl;
            return false;
        }
    }

    //(grandParentNode->height) -= 2; // assigning to final height
    // heights of the others will be the same finally as they are now

    // Let T3 be the right child of parentNode (i.e. of y, using notation
    // from Prof. Garg's lectures
    TreeNode *T3 = parentNode->right;

    // Now replicate the single rotation for LeftLeft as from the lecture
    // notes/video using *ONLY* calls to updateAVLParentChild

    // Make parentNode (y in Prof. Naveen Garg's lectures) the appropriate
    // child of greatGrandParentNode
    updateAVLParentChild(parentNode, greatGrandParentNode, isGPLeftChild);

    // Make currNode (x in Prof. Garg's lectures) the left child of
    // parentNode (y in Prof. Garg's lectures)
    // The last parameter is "true" to indicate that currNode should be
    // made the left child of parentNode
    // updateAVLParentChild(currNode, parentNode, true); // why?

    // Make grandParentNode (z in Prof. Garg's lectures) the right child of
    // parentNode (y in Prof. Garg's lectures)
    // The last parameter is "false" to indicate that grandParentNode
    // should NOT be made the left child of parentNode
    updateAVLParentChild(grandParentNode, parentNode, false);

    // Recall from Prof. Garg's lectures that the left and right subtrees
    // of currNode (i.e. x in Prof. Garg's lectures) stay unchanged after
    // the LeftLeft rotation.  So do don't need to update the children of
    // currNode at all.
    // Similarly, the right subtree of grandParentNode (i.e. z in Prof.
    // Garg's lectures) stays unchanged.  Hence, the right child of
    // grandParentNode doesn't need to be updated at all.
    // The only update needed is that the right subtree of parentNode (i.e.
    // y in Prof. Garg's notes) should now become the left
    // child of grandParentNode (i.e. of z in Prof. Garg's notes).

    // We use "true" as the third argument of the following call to indicate
    // that T3 should become the left child of grandParentNode
    updateAVLParentChild(T3, grandParentNode, true);

    return true;
}

bool AVLTree::rotateLeftRight(TreeNode *currNode, TreeNode *parentNode, TreeNode *grandParentNode)
{
    // Going back to Prof. Naveen Garg's lecture, x is *currNode,
    // y is *parentNode and z is *grandParentNode

    // Moreover, currNode is the right child of parentNode, and
    // parentNode is the left child of grandParentNode.  That's
    // why we are doing a rotateLeftRight

    TreeNode *greatGrandParentNode = grandParentNode->parent;

    // First find if grandParentNode is the left or right child of
    // greatGrandParentNode

    bool isGPLeftChild;
    if(greatGrandParentNode != nullptr)
    {
        if (greatGrandParentNode->left == grandParentNode)
        {
            isGPLeftChild = true;
        }
        else if (greatGrandParentNode->right == grandParentNode)
        {
            isGPLeftChild = false;
        }
        else
        {
            cerr << "Unexpected condition encountered!" << endl;
            return false;
        }
    }

    /*(grandParentNode->height) -= 2; // assigning to final heights
    --(parentNode->height);
    ++(currNode->height);*/
    // heights of the others will be the same finally as they are now

    // Let T2 be the left child of currNode (i.e. of x)
    TreeNode *T2 = currNode->left;

    // Let T3 be the right child of currNode (i.e. of x)
    TreeNode *T3 = currNode->right;

    // Now replicate the double rotation for LeftRight as from the lecture
    // notes/video using *ONLY* calls to updateAVLParentChild
    //
    // We can directly implement the double rotation, instead of doing two
    // rotations sequentially.  So we'll look at the end-result of the
    // double rotation (refer Prof. Garg's lecture notes) and arrive at that
    // from the original tree.

    // Make currNode (x in Prof. Naveen Garg's lectures) the appropriate
    // child of greatGrandParentNode
    updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);

    // Make parentNode (y in Prof. Garg's lectures) the left child of
    // currNode (x in Prof. Garg's lectures)
    // The last parameter is "true" to indicate that parentNode should be
    // made the left child of currNode
    updateAVLParentChild(parentNode, currNode, true);

    // Make grandParentNode (z in Prof. Garg's lectures) the right child of
    // currNode (x in Prof. Garg's lectures)
    // The last parameter is "false" to indicate that grandParentNode
    // should NOT be made the left child of currNode
    updateAVLParentChild(grandParentNode, currNode, false);

    // Recall from Prof. Garg's lectures that the left subtree of
    // parentNode (i.e. y in Prof. Garg's lectures) and right subtree of
    // grandParentNode (i.e. z in Prof. Garg's lectures) stay unchanged
    // after the LeftRight rotation.  So do don't need to update the
    // left child of parentNode and the right child of grandParentNode
    // at all.
    // The only update needed is that the left subtree of currNode (i.e.
    // x in Prof. Garg's notes) should now become the right subtree of
    // parentNode (y in Prof. Garg's notes).  Similarly, the right subtree
    // of currNode (i.e. of x) should now become the left subtree of
    // grandParentNode (i.e. of z).

    // Let's implement these updations below.

    // We use "false" as the third argument of the following call to indicate
    // that T2 should NOT become the left child of ParentNode
    updateAVLParentChild(T2, parentNode, false);

    // We use "true" as the third argument of the following call to indicate
    // that T3 should become the left child of grandParentNode
    updateAVLParentChild(T3, grandParentNode, true);

    return true;
}

bool AVLTree::rotateRightLeft(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
    // Implement this yourself
    // grandParent->right == parent
    // parent->left == currNode

    TreeNode* greatGrandParentNode = grandParent->parent;

    bool isGPLeftChild;
    if(greatGrandParentNode != nullptr)
    {
        if (greatGrandParentNode->left == grandParent)
        {
            isGPLeftChild = true;
        }
        else if (greatGrandParentNode->right == grandParent)
        {
            isGPLeftChild = false;
        }
        else
        {
            cerr << "Unexpected condition encountered!" << endl;
            return false;
        }        
    }

    /*(grandParent->height) -= 2; // assigning to final heights
    --(parent->height);
    ++(currNode->height);*/
    // heights of the others will be the same

    TreeNode* T2 = currNode->left;
    TreeNode* T3 = currNode->right;

    updateAVLParentChild(currNode, greatGrandParentNode, isGPLeftChild);
    updateAVLParentChild(grandParent, currNode, true);
    updateAVLParentChild(parent, currNode, false);
    updateAVLParentChild(T2, grandParent, false);
    updateAVLParentChild(T3, parent, true);

    return true;
}

bool AVLTree::rotateRightRight(TreeNode *currNode, TreeNode *parent, TreeNode *grandParent)
{
    // Implement this yourself
    // grandParent->right == parent
    // parent->right == current

    TreeNode* greatGrandParentNode = grandParent->parent;

    bool isGPLeftChild;
    if(greatGrandParentNode != nullptr)
    {
        if (greatGrandParentNode->left == grandParent)
        {
            isGPLeftChild = true;
        }
        else if (greatGrandParentNode->right == grandParent)
        {
            isGPLeftChild = false;
        }
        else
        {
            cerr << "Unexpected condition encountered!" << endl;
            return false;
        }        
    }

    //(grandParent->height) -= 2; // assigning to final height
    // heights of the others will be the same finally as they are now

    TreeNode* T2 = parent->left;
    updateAVLParentChild(parent, greatGrandParentNode, isGPLeftChild);
    updateAVLParentChild(grandParent, parent, true);
    updateAVLParentChild(T2, grandParent, false);


    return true;
}

// Returns true on successful insertion in AVL tree. Returns false otherwise.
// You may assume that no two elements being inserted have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::insert(int jrnyCode, int price)
{
    // Implement insertion in AVL tree followed by balance factor restoration
    // by properly identifying x, y, z as used in Prof. Garg's lectures
    // (equivalently, currNode, parentNode, grandParentNode in our code) and
    // invoking rotateLeftLeft, rotateLeftRight, rotateRightLeft and/or
    // rotateRightRight as appropriate.

    // It is your responsibility to find out the right x, y, z (or currNode,
    // parentNode, grandParentNode) following Prof. Garg's lectures
    //
    // Once you identify these correctly, simply invoking the appropriate
    // rotation should do the job.
    // You don't even need to invoke rotation twice for the double
    // rotations -- the way rotationLeftRight is implemented, and
    // rotationRightLeft should be implemented, you should be able to achieve
    // the effect of the double rotation using one invokation of the
    // appropriate member function.

    // You MUST use only AVLLessThan to compare two journey codes.  You
    // can create a new node containing the journey code to be inserted
    // and invoke AVLLessThan on the current node in the tree that you
    // are inspecting and the new node to do your comparison.

    // REMEMBER to update the heights of appropriate nodes in the tree
    // after an insertion.

    // We use "return true" below to enable compilation.  Change this as you
    // see fit.

    TreeNode temp(jrnyCode, price);
    TreeNode* parent = nullptr;
    TreeNode* curr = root;
    TreeNode* gc;
    bool is_left = false;
    while(true)
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
                root = curr; // height already 0
                return true;
            }

            gc = AVL_update_heights(curr);
            if(gc == nullptr)
            {
                return true; // tree is not unabalanced after insertion
            }
            break;
        }
        else if(AVLLessThan(&temp, curr))
        {
            is_left = true;
            parent = curr;
            curr = curr->left;
        }
        else if(AVLLessThan(curr, &temp))
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

    /*while(true)
    {
        if(curr == nullptr /* not possible  || curr->parent == nullptr || curr->parent->parent == nullptr)
        {
            return true; // tree was not unbalanced
        }
        
        if(abs(imbalance(curr->parent->parent)) > 1) break;
        curr = curr->parent;
    }*/

    if(AVLisLeftChild(gc->parent))
    {
        if(AVLisLeftChild(gc))
        {
            (gc->parent->parent->height) -= 2; // assigning to final height
            // heights of the others will be the same finally as they are now
            rotateLeftLeft(gc, gc->parent, gc->parent->parent);
        }
        else
        {
            (gc->parent->parent->height) -= 2; // assigning to final heights
            --(gc->parent->height);
            ++(gc->height);
            // heights of the others will be the same finally as they are now
            rotateLeftRight(gc, gc->parent, gc->parent->parent);
        }
    }
    else
    {
        if(AVLisLeftChild(gc))
        {
            (gc->parent->parent->height) -= 2; // assigning to final heights
            --(gc->parent->height);
            ++(gc->height);
            // heights of the others will be the same

            rotateRightLeft(gc, gc->parent, gc->parent->parent);
        }
        else
        {
            (gc->parent->parent->height) -= 2; // assigning to final height
            // heights of the others will be the same finally as they are now
            rotateRightRight(gc, gc->parent, gc->parent->parent);
        }
    }

    return true;
}

// Returns the price on finding an element in the AVL tree that matches
// journey code. Returns -1 otherwise.
// You may assume that no two node in the tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

int AVLTree::find(int jrnyCode)
{
    // Implement find in AVL tree.
    // This is really no different from finding in a binary search tree.
    // This operation cannot cause any balance factor disturbances.

    // You MUST use only AVLLessThan to compare two journey codes.  You
    // can create a new node containing the journey code to be searched
    // (along with some arbitrary price) and invoke AVLLessThan on the
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
        else if(AVLLessThan(&temp, curr))
        {
            curr = curr->left;
        }
        else if(AVLLessThan(curr, &temp))
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

// node should be a leaf with a parent
void AVL_delete(TreeNode* node)
{
    TreeNode* pr = node->parent;
    if(AVLisLeftChild(node))
    {
        pr->left = nullptr;
        delete node;
        if(pr->left->height)
    }
    else
    {
        pr->right = nullptr;
        delete node;
    }
}

void AVL_remove_node(TreeNode* node, TreeNode** root_ptr)
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
            /*TreeNode* pr = node->parent;
            if(AVLisLeftChild(node))
            {
                pr->left = nullptr;
            }
            else
            {
                pr->right = nullptr;
            }
            delete node;
            // BST_update_heights(pr);*/
            AVL_delete(node);
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
            /*TreeNode* pr = node->parent;
            if(AVLisLeftChild(node))
            {
                pr->left = node->right;
            }
            else
            {
                pr->right = node->right;
            }

            delete node;*/
            TreeNode* pr = node->parent;
            TreeNode* left = node->left;
            TreeNode* right = node->right;
            int h = node->height;
            *node = *(node->right);
            node->parent = pr;
            node->left = left;
            node->right = right;
            node->height = h;

            AVL_delete(node->right);

            // BST_update_heights(pr);
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
            /*TreeNode* pr = node->parent;
            if(AVLisLeftChild(node))
            {
                pr->left = node->left;
            }
            else
            {
                pr->right = node->left;
            }

            delete node;*/

            TreeNode* pr = node->parent;
            TreeNode* left = node->left;
            TreeNode* right = node->right;
            int h = node->height;
            *node = *(node->left);
            node->parent = pr;
            node->left = left;
            node->right = right;
            node->height = h;

            AVL_delete(node->left);

            // BST_update_heights(pr);
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

        /*TreeNode* trp = tr->parent;
        if(AVLisLeftChild(tr))
        {
            trp->left = tr->left;
        }
        else
        {
            trp->right = tr->left;
        }

        delete tr;*/
        if(tr->left == nullptr) AVL_delete(tr);
        else
        {
            TreeNode* par = tr->parent;
            TreeNode* lf = tr->left;
            TreeNode* rg = tr->right;
            int h = tr->height;
            *tr = *(tr->left);
            AVL_delete(tr->left);
        }

        // BST_update_heights(tr);
    }
}

// Returns true on successful deletion of the entry in AVL tree with
// matching journey code. Returns false if it cannot find any such element.
//
// You may assume that no two elements in the AVL tree have the same journey
// code, and journey code is the key for insertion and finding in the AVL
// tree.

bool AVLTree::remove(int jrnyCode)
{
    // Implement deletion in AVL tree followed by balance factor restoration
    // by properly identifying x, y, z as used in Prof. Garg's lectures
    // (equivalently, currNode, parentNode, grandParentNode in our code) and
    // invoking rotateLeftLeft, rotateLeftRight, rotateRightLeft and/or
    // rotateRightRight as appropriate.

    // It is your responsibility to find out the right x, y, z (or currNode,
    // parentNode, grandParentNode) following Prof. Garg's lectures
    //
    // Once you identify these correctly, simply invoking the appropriate
    // rotation(s) should do the job.
    // You don't even need to invoke rotation twice for the double
    // rotations -- the way rotationLeftRight is implemented, and
    // rotationRightLeft should be implemented, you should be able to achieve
    // the effect of the double rotation using one invokation of the
    // appropriate member function.

    // You MUST use only AVLLessThan to compare two journey codes.  You
    // can create a new node containing the journey code to be searched
    // (along with some arbitrary price) and invoke AVLLessThan on the
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
        else if(AVLLessThan(&temp, curr))
        {
            curr = curr->left;
        }
        else if(AVLLessThan(curr, &temp))
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
