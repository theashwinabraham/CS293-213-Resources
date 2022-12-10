/*
 * IMPLEMENTED BY: ASHWIN ABRAHAM
 */

// Code up the functions defined in tree.h
// Reuse the binary Search Tree implemented in lab 3 as much as possible


#include "tree.h"



// Constructors: There are 3 variants of the constructor given below.
// Please make sure you understand what each of these variants do.
// Ask your TA or the instructor if you have a doubt.

TreeNode::TreeNode() : price(0), JourneyCode(0), left(nullptr), right(nullptr), shortestPathLength(0), longestPathLength(0) {}

TreeNode::TreeNode(int jrnyCode, int jrnyPrice) : price(jrnyPrice), JourneyCode(jrnyCode), left(nullptr), right(nullptr), shortestPathLength(0), longestPathLength(0) {}

TreeNode::TreeNode(int jrnyCode, int jrnyPrice, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : price(jrnyPrice), JourneyCode(jrnyCode), left(leftChild), right(rightChild), parent(parent)
{
    if(left == nullptr && right == nullptr)
    {
        shortestPathLength = longestPathLength = 0;
        return;
    }
    if(left == nullptr || right == nullptr)
    {
        shortestPathLength = 0;
        longestPathLength = 1 + (left == nullptr? right : left)->longestPathLength;
        return;
    }
    shortestPathLength = 1 + (left->shortestPathLength < right->shortestPathLength ? left->shortestPathLength : right->shortestPathLength);
    longestPathLength = 1 + (left->longestPathLength < right->longestPathLength ? right->longestPathLength : left->longestPathLength);
    return;
}


// updates lengths of the entire path from the current node to root (both inclusive)
// if node->left is not null and has correct lengths, pass argument as true
// if node->right is not null and has correct lengths, pass argument as false
void TreeNode::update_lengths(bool start_left)
{
    for(TreeNode* current = (start_left? left : right); current != nullptr; current = current->parent)
    {
        if(current->parent == nullptr)
        {
            /* no\op */
        }
        else if(current->parent->left == current)
        {
            if(current->parent->right == nullptr)
            {
                current->parent->shortestPathLength = 0;
                current->parent->longestPathLength = 1 + current->longestPathLength;
            }
            else
            {
                if(current->shortestPathLength < current->parent->right->shortestPathLength)
                {
                    current->parent->shortestPathLength = 1 + current->shortestPathLength;
                }
                else
                {
                    current->parent->shortestPathLength = 1 + current->parent->right->shortestPathLength;
                }

                if(current->longestPathLength < current->parent->right->longestPathLength)
                {
                    current->parent->longestPathLength = 1 + current->parent->right->longestPathLength;
                }
                else
                {
                    current->parent->longestPathLength = 1 + current->longestPathLength;
                }
            }
        }
        else /* if(current->parent->right == current) */
        {
            if(current->parent->left == nullptr)
            {
                current->parent->shortestPathLength = 0;
                current->parent->longestPathLength = 1 + current->longestPathLength;
            }
            else
            {
                if(current->shortestPathLength < current->parent->left->shortestPathLength)
                {
                    current->parent->shortestPathLength = 1 + current->shortestPathLength;
                }
                else
                {
                    current->parent->shortestPathLength = 1 + current->parent->left->shortestPathLength;
                }

                if(current->longestPathLength < current->parent->left->longestPathLength)
                {
                    current->parent->longestPathLength = 1 + current->parent->left->longestPathLength;
                }
                else
                {
                    current->parent->longestPathLength = 1 + current->longestPathLength;
                }
            }
        }
    }
}

int TreeNode::getImbalance()
{
    // Returns how imbalanced the paths starting from this node to the
    // leaves are.  A case of perfect balance would result in the
    // longest and shortest path lengths being equal, so their difference
    // will be 0 (i.e. 0 imbalance).
    // Think about when would we have a case of large imbalance.

    return (longestPathLength - shortestPathLength);
}

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise

int BST::getImbalance()
{
    if (root == nullptr)
        return 0;
    else
        return root->getImbalance();
}

bool BST::insert(int JourneyCode, int price)
{
    // The following filler code snippet is only given to facilitate
    // compilation.  You should replace/augment it with appropriate code,
    // similar to what you had done in lab assignment 3.

    /*struct TreeNode *currNode = root, *parentOfCurrNode = nullptr;

    while (currNode != nullptr)
    {
        if (currNode->JourneyCode < JourneyCode)
        {
            parentOfCurrNode = currNode;
            currNode = currNode->right;
        }
        else if (currNode->JourneyCode > JourneyCode)
        {
            parentOfCurrNode = currNode;
            currNode = currNode->left;
        }
        else
        { // currNode->JourneyCode == JourneyCode
            return false;
        }
    }*/
    // JourneyCode is not present in the BST.  We must now
    // insert an appropriate child of parentOfCurrNode.
    // Please implement this part yourself.
    //
    // Do not forget to update shortestPathLength and
    // longestPathLength of (possibly all) BST nodes in the
    // path from the root to the new node you are inserting

    // checking if JourneyCode is present in BST
    static bool checked = false; // prevents find being executed every recursive call
    if(!checked)
    {
        checked = true;
        if(find(JourneyCode))
        {
            checked = false;
            return false;
        }
    }
    if(root == nullptr)
    {
        root = new TreeNode(JourneyCode, price, nullptr, nullptr, nullptr);
        checked = false;
        return true;
    }
    if(JourneyCode <= root->JourneyCode)
    {
        if(root->left == nullptr)
        {
            root->left = new TreeNode(JourneyCode, price, nullptr, nullptr, root);
            root->update_lengths(true);
            checked = false;
            return true;
        }
        return BST(root->left).insert(JourneyCode, price);
    }
    /*if(JourneyCode > root->JourneyCode)*/
    if(root->right == nullptr)
    {
        root->right = new TreeNode(JourneyCode, price, nullptr, nullptr, root);
        root->update_lengths(false);
        checked = false;
        return true;
    }
    return BST(root->right).insert(JourneyCode, price);
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    // The following filler code snippet is only given to facilitate
    // compilation.  You should replace it with appropriate code, very
    // similar to what you had done in lab assignment 3.
    //
    // You can look at the implementation of insert to code this part up.

    if(root == nullptr) return false;
    if(root->JourneyCode == JourneyCode && root->price == price) return true;
    if(JourneyCode <= root->JourneyCode) return BST(root->left).find(JourneyCode, price);
    /*if(price > root->price)*/ return BST(root->right).find(JourneyCode, price);
}

// finds if a JourneyCode is present in the tree
bool BST::find(int JourneyCode)
{
    if(root == nullptr) return false;
    if(root->JourneyCode == JourneyCode) return true;
    if(JourneyCode < root->JourneyCode) return BST(root->left).find(JourneyCode);
    /* if(JourneyCode > root->JourneyCode) */ return BST(root->right).find(JourneyCode);
}

void BST::remove_node(TreeNode* node)
{
    if(node == nullptr) return;

    if(node->left == nullptr && node->right == nullptr)
    {
        if(node->parent != nullptr)
        {
            if(node->parent->left == node)
            {
                node->parent->left = nullptr;
                if(node->parent->right == nullptr)
                {
                    node->parent->shortestPathLength = node->parent->longestPathLength = 0;
                }
                else node->parent->update_lengths(false);
            }
            else
            {
                node->parent->right = nullptr;
                if(node->parent->left == nullptr)
                {
                    node->parent->longestPathLength = node->parent->shortestPathLength = 0;
                }
                else node->parent->update_lengths(true);
            }
        }
        else root = nullptr;
    }
    else if(node->left == nullptr && node->right != nullptr)
    {
        node->right->parent = node->parent;
        if(node->parent != nullptr)
        {
            if(node->parent->left == node)
            {
                node->parent->left = node->right;
                node->parent->update_lengths(true);
            }
            else
            {
                node->parent->right = node->right;
                node->parent->update_lengths(false);
            }
        }
        else root = node->right;
    }
    else if(node->left != nullptr && node->right == nullptr)
    {
        node->left->parent = node->parent;
        if(node->parent != nullptr)
        {
            if(node->parent->left == node)
            {
                node->parent->left = node->left;
                node->parent->update_lengths(true);
            }
            else
            {
                node->parent->right = node->left;
                node->parent->update_lengths(false);
            }
        }
        else root = node->left;
    }
    else
    {
        TreeNode* pred = node->left; // We will make this point to the node with the largest key that is less than or equal to root key
        while(pred->right != nullptr)
        {
            pred = pred->right;
        }
        node->JourneyCode = pred->JourneyCode;
        node->price = pred->price;
        if(pred->left != nullptr)
        {
            pred->left->parent = pred->parent;
            if(pred->parent->left == pred)
            {
                pred->parent->left = pred->left;
                pred->parent->update_lengths(true);
            }
            else
            {
                pred->parent->right = pred->left;
                pred->parent->update_lengths(false);
            }
        }
        else
        {
            if(pred->parent->left == pred)
            {
                pred->parent->left = nullptr;
                if(pred->parent->right != nullptr)
                {
                    pred->parent->update_lengths(false);
                }
                else
                {
                    pred->parent->shortestPathLength = pred->parent->longestPathLength = 0;
                }
            }
            else
            {
                pred->parent->right = nullptr;
                if(pred->parent->left != nullptr)
                {
                    pred->parent->update_lengths(true);
                }
                else
                {
                    pred->parent->shortestPathLength = pred->parent->longestPathLength = 0;
                }
            }
        }
    }
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
    // The following filler code snippet is only given to facilitate
    // compilation.  You should replace it with appropriate code, very
    // similar to what you had done in lab assignment 3.
    //
    // Recall from CS 213 lectures about the various ways in which the
    // BST can be restructured when a node is deleted. You can implement
    // any of these alternatives.
    //
    // Do not forget to update shortestPathLength and
    // longestPathLength of (possibly all) BST nodes in the
    // path from the root to nodes whose position in the BST is affected
    // by the remove.

    if(root == nullptr) return false;
    if(price == root->price && JourneyCode == root->JourneyCode)
    {
        remove_node(root);
        return true;
    }
    return BST(JourneyCode <= root->JourneyCode ? root->left : root->right).remove(JourneyCode, price);
}

// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
void BST::printBST(const std::string &prefix, bool isLeft /*= false*/)
{
    if (root != nullptr)
    {
        std::cout << prefix;

        std::cout << (isLeft ? "|--" : "|__");

        // print the value of the node
        std::cout << root->JourneyCode << std::endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST(prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST(prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::getBST(const std::string &prefix, bool isLeft /*= false*/)
{
    if (root != nullptr)
    {
        result.push_back(prefix);

        result.push_back(isLeft ? "|--" : "|__");

        // print the value of the node
        result.push_back(std::to_string(root->JourneyCode) + "\n");
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        getBST(prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        getBST(prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::clearResult()
{
    result.clear();
}

std::vector<std::string> BST::getResult()
{
    return result;
}
