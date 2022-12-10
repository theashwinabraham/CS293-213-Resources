#ifndef TREE_H
#include "Tree.h"
#endif

#ifndef BST_H
#include "BST.cpp"
#endif

#ifndef AVL_H
#include "AVL.cpp"
#endif

#ifndef STD_HEADERS
#include <iostream>
#include <stdlib.h>
#endif

#include <fstream>

using namespace std;

int main(int argc, char **argv)
{
    AVLTree *treeAVL;
    BST *treeBST;
    ofstream statFile;
    int choice = -1;
    string cmd;

    // if (argc == 1) {
    //     statFile.open((choice == 0) ? "BST.out" : "AVL.out");
    // } else {
    //     cout.setstate(ios_base::failbit);
    //     statFile.open(argv[1]);
    // }

    cout << "0. BST\n1. AVL\nChoose type of tree : ";
    cin >> choice;
    statFile.open((choice == 0) ? "BST.out" : "AVL.out");

    int perComparisonCost, perParentChildUpdateCost;

    cout << "Enter per comparison cost (non-negative integer): ";
    cin >> perComparisonCost;
    cout << "Enter per parent-child update cost (non-negative integer): ";
    cin >> perParentChildUpdateCost;

    if (perComparisonCost <= 0)
    {
        cout << "Invalid per comparison cost.  Defaulting to 1" << endl;
        perComparisonCost = 1;
    }
    if (perParentChildUpdateCost <= 0)
    {
        cout << "Invalid per parent-child update cost.  Defaulting to 1" << endl;
        perParentChildUpdateCost = 1;
    }

    if (choice == 0)
    {
        treeBST = new BST(perComparisonCost, perParentChildUpdateCost);
    }
    else if (choice == 1)
    {
        treeAVL = new AVLTree(perComparisonCost, perParentChildUpdateCost);
    }
    else
    {
        cout << "Invalid Choice" << endl;
        return 0;
    }

    cout << ">>";
    while (cin >> cmd)
    {
        if (cmd == "ADD")
        {
            int jCode, price;
            cin >> jCode >> price;

            if (((choice == 0) ? treeBST->insert(jCode, price) : treeAVL->insert(jCode, price)))
            {
                cout << "SUCCESSFULLY ADDED" << endl;
            }
            else
            {
                cout << "INSERT FAILED" << endl;
            }
            statFile << ((choice == 0) ? treeBST->getComparisonCost() : treeAVL->getComparisonCost()) << " " << ((choice == 0) ? treeBST->getParentChildUpdateCost() : treeAVL->getParentChildUpdateCost()) << endl;
        }
        else if (cmd == "DEL")
        {
            int jCode;
            cin >> jCode;

            if ((choice == 0) ? treeBST->remove(jCode) : treeAVL->remove(jCode))
            {
                cout << "SUCCESSFULLY DELETED" << endl;
            }
            else
            {
                cout << "DELETION FAILED" << endl;
            }
            statFile << ((choice == 0) ? treeBST->getComparisonCost() : treeAVL->getComparisonCost()) << " " << ((choice == 0) ? treeBST->getParentChildUpdateCost() : treeAVL->getParentChildUpdateCost()) << endl;
        }
        else if (cmd == "FIND")
        {
            int jCode;
            cin >> jCode;

            int price = ((choice == 0) ? treeBST->find(jCode) : treeAVL->find(jCode));
            if (price >= 0)
            {
                cout << "FOUND" << endl;
            }
            else
            {
                cout << "NOT FOUND" << endl;
            }
            statFile << ((choice == 0) ? treeBST->getComparisonCost() : treeAVL->getComparisonCost()) << " " << ((choice == 0) ? treeBST->getParentChildUpdateCost() : treeAVL->getParentChildUpdateCost()) << endl;
        }
        else if (cmd == "PRINT")
        {
            if (choice == 0)
            {
                treeBST->print();
            }
            else
            {
                treeAVL->print();
            }
        }
        else if (cmd == "EXIT")
        {
            break;
        }
        cout << ">>";
    }
    statFile.close();
    if (choice == 0)
    {
        delete treeBST;
    }
    else
    {
        delete treeAVL;
    }

    return 0;
}
