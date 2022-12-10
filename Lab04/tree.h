#ifndef BST_H
#define BST_H

#include <iostream>
#include <vector>
#include <string>

// Header file for defining a Binary Search Tree
// Reuse the binary Search Tree implemented in lab 3 as much as possible

// struct TreeNode given below is almost the same as was given to you
// in lab 3. The only exception is the addition of shortestPathLength
// and longestPathLength fields along with a member function getImbalance.
// Read the comments in the structure definition to understand the meanings
// of these.
//

struct TreeNode
{
    int JourneyCode;        // Journey code
    int price;              // Price
    TreeNode *left;         // Left Child of this Node (NULL, if None)
    TreeNode *right;        // Right Child of this Node (NULL, if None)
    TreeNode *parent;       // The Parent Node, NULL in case of Root
    int shortestPathLength; // Length of shortest path from this node to a leaf where a nullptr leaf contributes a path of length 0
    int longestPathLength;  // Length of longest path from this node to a leaf where a nullptr leaf contributes a path of length 0

    // Constructors: There are 3 variants of the constructor given below.
    // Please make sure you understand what each of these variants do.
    // Ask your TA or the instructor if you have a doubt.

    TreeNode();

    TreeNode(int, int);

    TreeNode(int, int, TreeNode*, TreeNode*, TreeNode*);

    // updates lengths of the entire path from the current node to root (both inclusive)
    // if node->left is not null and has correct lengths, pass argument as true
    // if node->right is not null and has correct lengths, pass argument as false
    void update_lengths(bool start_left);

    int getImbalance();
    // Returns how imbalanced the paths starting from this node to the
    // leaves are.  A case of perfect balance would result in the
    // longest and shortest path lengths being equal, so their difference
    // will be 0 (i.e. 0 imbalance).
    // Think about when would we have a case of large imbalance.

};

// class BST given below is a slight modification of what it was in
// lab 3.  A few new fields have been introduced, and some member functions
// have been removed, since they are no longer needed for the current
// assignment.

// Note however that unlike in lab 3 where you had to build the BST using
// ordering of prices, this time we will build the BST using ordering of
// journey codes.

class BST {
    // Feel free to add more private/public variables and/or functions
    // But do not modify the pre-existing function signatures

    TreeNode *root;

    // result variable is for testing purposes, Do not tamper with it!
    std::vector<std::string> result;

    // removes a given node from the Tree
    void remove_node(TreeNode*);


public:
    // ************************************************************
    // Methods for Part I

    // Constructors!
    BST() { root = nullptr; }
    BST(TreeNode *curr_root) { root = curr_root; }

    // Implement your own destructor
    // ~BST(){};

    // Returns false, if given JourneyCode is already present in the BST
    // Inserts the element and returns True otherwise
    bool insert(int JourneyCode, int price);

    // Return true, if the ticket with given attributes is found, false otherwise
    bool find(int JourneyCode, int price);

    bool find(int JourneyCode);

    // Returns false, if JourneyCode isn't present
    // Deletes the corresponding entry and returns True otherwise
    bool remove(int JourneyCode, int price);

    // Returns the imbalance of the root node of the BST
    int getImbalance();

    // This function prints the BST using ASCII characters using the
    // format:
    //
    //   root
    //       |-- left subtree
    //       |__ right subtree
    //
    // where the left and right subtrees are printed recursively in
    // the same format.
    //
    // We have done this for you! Please see BST.cpp for details
    // You may use this for debugging purposes.
    //
    void printBST(const std::string &prefix, bool isLeft = false);

    // The three functions below are for evaluation purposes, Do not tamper with them!
    void getBST(const std::string &prefix, bool isLeft = false);
    void clearResult();
    std::vector<std::string> getResult();
};

#endif