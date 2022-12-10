#ifndef SORT_H
#define SORT_H

#include <cstdlib>
#include "tree.h"
#include "choose.h"
#include "journey.h"

class SorterTree {
private:
    static Journey* (*choices[3])(Journey*, int, int);
    Journey *array;
    BST *tree;
    int choice;      // Choice of pivot function to use
    int l;           // Total number of entries
    int alloc_len; // allocated length
    int comparisons; // Total number of comparisons performed

public:
    SorterTree(int choice, int l);                      // Define valid constructor /
    bool Quicksort(int start, int finish);              // Sort the array according to the stored values /
    bool QuicksortWithBSTInsert(int start, int finish); // May need extra parameters depending on implementation /
    bool printArray(); // /
    void insert(int JourneyCode, int price); // insert into array /
    bool insertPivot(int JourneyCode, int price); // insert node corresponding to chosen pivot in BST /
    BST *getTree();                               // returns pointer to the tree of pivots /
    ~SorterTree();                                // Destructor /
};

#endif
