/*
 * IMPLEMENTED BY: ASHWIN ABRAHAM
 */

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

#include "BST.h"

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
#define LOAD_LEFT_SUBTREE 4

// PLEASE FILL IN THE BODIES OF THE FOLLOWING FUNCTIONS

BST::BST(): root(nullptr) {}
BST::BST(TreeNode *root): root(root) {}

// Returns false, if given JourneyCode is already present in the BST
// Inserts the element and returns True otherwise
bool BST::insert(int JourneyCode, int price)
{
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
    if(price <= root->price)
    {
        if(root->left == nullptr)
        {
            root->left = new TreeNode(JourneyCode, price, nullptr, nullptr, root);
            checked = false;
            return true;
        }
        return BST(root->left).insert(JourneyCode, price);
    }
    /*if(price > root->price)*/
    if(root->right == nullptr)
    {
        root->right = new TreeNode(JourneyCode, price, nullptr, nullptr, root);
        checked = false;
        return true;
    }
    return BST(root->right).insert(JourneyCode, price);
}

// Return True, if the ticket with given attributes is found, false otherwise
bool BST::find(int JourneyCode, int price)
{
    if(root == nullptr) return false;
    if(root->price == price && root->JourneyCode == JourneyCode) return true;
    if(price <= root->price) return BST(root->left).find(JourneyCode, price);
    /*if(price > root->price)*/ return BST(root->right).find(JourneyCode, price);
}

// finds if a JourneyCode is present in the tree
bool BST::find(int JourneyCode)
{
    if(root == nullptr) return false;
    if(root->JourneyCode == JourneyCode) return true;
    return BST(root->left).find(JourneyCode) || BST(root->right).find(JourneyCode);
}


void BST::remove_node(TreeNode* node)
{
    if(node == nullptr) return;

    if(node->left == nullptr && node->right == nullptr)
    {
        if(node->parent != nullptr)
        {
            if(node->parent->left == node) node->parent->left = nullptr;
            else node->parent->right = nullptr;
        }
        else root = nullptr;
    }
    else if(node->left == nullptr && node->right != nullptr)
    {
        node->right->parent = node->parent;
        if(node->parent != nullptr)
        {
            if(node->parent->left == node) node->parent->left = node->right;
            else node->parent->right = node->right;
        }
        else root = node->right;
    }
    else if(node->left != nullptr && node->right == nullptr)
    {
        node->left->parent = node->parent;
        if(node->parent != nullptr)
        {
            if(node->parent->left == node) node->parent->left = node->left;
            else node->parent->right = node->left;
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
        if(pred->left != nullptr) pred->left->parent = pred->parent;
        if(pred->parent->left == pred) pred->parent->left = pred->left;
        else pred->parent->right = pred->left;
    }
}

// Returns false, if JourneyCode isn't present
// Deletes the corresponding entry and returns True otherwise
bool BST::remove(int JourneyCode, int price)
{
    if(root == nullptr) return false;
    if(price == root->price && JourneyCode == root->JourneyCode)
    {
        remove_node(root);
        return true;
    }
    return BST(price <= root->price ? root->left : root->right).remove(JourneyCode, price);
}

// Functions that traverse the BST in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the BST in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void BST::traverse(int typeOfTraversal)
{
    if(root == nullptr) return;
    if(typeOfTraversal == PRE_ORDER) std::cout << root->JourneyCode << '\n';
    BST(root->left).traverse(typeOfTraversal);
    if(typeOfTraversal == IN_ORDER) std::cout << root->JourneyCode << '\n';
    BST(root->right).traverse(typeOfTraversal);
    if(typeOfTraversal == POST_ORDER) std::cout << root->JourneyCode << '\n';
}

// Returns the price of the cheapest journey
int BST::getMinimum()
{
    if(root->left == nullptr) return root->price;
    return BST(root->left).getMinimum();
}

// Part II

// Returns the count of journeys that are at least as expensive
// as lowerPriceBound and at most as expensive as upperPriceBound,
// both bounds included.
int BST::countJourneysInPriceBound(int lowerPriceBound, int upperPriceBound)
{
    if(root == nullptr) return 0;
    if(root->price < lowerPriceBound) return BST(root->right).countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
    if(root->price <= upperPriceBound) return 1 + BST(root->left).countJourneysInPriceBound(lowerPriceBound, upperPriceBound) + BST(root->right).countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
    /*if(root->price > upperPriceBound)*/ return BST(root->left).countJourneysInPriceBound(lowerPriceBound, upperPriceBound);
}

// Store the current tree in a file called filename.  You should
// store using a scheme that uses no more disk space than that
// required to store all elements in the BST, plus perhaps a small
// constant times the number of elements.  You should also store
// in a manner such that your implementation of customLoad is as
// memory and time efficient as possible.

// 
void BST::customStore(string filename)
{
    std::ofstream f(filename);
    myStore(f);
}

void BST::myStore(std::ofstream& out)
{
    static int recursion_level = 0;
    if(root == nullptr) return;
    out << root->JourneyCode << ' ' << root->price << '\n';
    ++recursion_level;
    BST(root->left).myStore(out);
    --recursion_level;
    out << "0 " << recursion_level << '\n';
    ++recursion_level;
    BST(root->right).myStore(out);
    --recursion_level;
}
	
// While loading a tree from a file written by customStore, we
// can have one of two modes of loading.  We could either ask
// for the entire tree to be loaded or only the left subtree of
// the root (if it exists) to be loaded.  The loadMode flag
// takes one of two values LOAD_FULL_BST or LOAD_LEFT_SUBTREE,
// that are #defined in BST.cpp.
// If loadMode is LOAD_FULL_BST, customLoad should load the
// entire BST that was stored in filename using customStore.
// If loadMode is LOAD_LEFT_SUBTREE, customLoad should load
// only the left subtree of the root of the BST that was
// stored in filename using customStore.
// Your implementation of customLoad should be efficient --
// its time and space complexity should be linear in the size
// of the tree that is being loaded.  So, for example, if the
// left sub-tree of the root is small compared to the right
// sub-tree, customLoad's time and space complexity should
// be small even though the entire BST may be very large.

 
void BST::customLoad(int flag, string filename)
{
    std::ifstream file(filename);
    if(flag == LOAD_FULL_BST)
    {
        int JC, pr;
        root = nullptr;
        TreeNode** current = &root;
        std::vector<TreeNode**> nodes;
        int level = 0;
        while(file >> JC >> pr)
        {
            if(JC != 0)
            {
                *current = new TreeNode(JC, pr);
                if(level == nodes.size()) nodes.push_back(current);
                else nodes[level] = current;

                current = &((*current)->left);
                ++level;
            }
            else
            {
                level = pr;
                current = nodes[level];

                current = &((*current)->right);
                ++level;
            }
        }
    }
    else if(flag == LOAD_LEFT_SUBTREE)
    {
        int JC, pr;
        root = nullptr;
        if(file >> JC >> pr)
        {
            TreeNode** current = &root;
            std::vector<TreeNode**> nodes;
            int level = 0;

            file >> JC >> pr;
            if(JC != 0)
            {
                *current = new TreeNode(JC, pr);
                if(level == nodes.size()) nodes.push_back(current);
                else nodes[level] = current;

                current = &((*current)->left);
                ++level;
            }
            else return;

            while(file >> JC >> pr)
            {
                if(JC != 0)
                {
                    *current = new TreeNode(JC, pr);
                    if(level == nodes.size()) nodes.push_back(current);
                    else nodes[level] = current;

                    current = &((*current)->left);
                    ++level;
                }
                else
                {
                    if(pr == 0) return;
                    level = pr-1;
                    current = nodes[level];

                    current = &((*current)->right);
                    ++level;
                }
            }
        }
    }
}

// Please use the following code to replace the last part of
// BST.cpp that was provided earlier (from below the comment
// DO NOT CHANGE ANYTHING BELOW THIS LINE)
//
//

// ************************************************************
// DO NOT CHANGE ANYTHING BELOW THIS LINE

// Adapted from Adrian Schneider's code on StackOverflow
void BST::printBST(const string& prefix, bool isLeft/*=false*/)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->JourneyCode << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::getBST(const string& prefix,  bool isLeft/*=false*/)
{
    if( root != nullptr )
    {
        result.push_back(prefix);

        result.push_back(isLeft ? "|--" : "|__" );

        // print the value of the node
        result.push_back(to_string(root->JourneyCode) + "\n");
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        getBST( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        getBST( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void BST::clearResult(){
    result.clear();
}

vector<string> BST::getResult(){
    return result;
}