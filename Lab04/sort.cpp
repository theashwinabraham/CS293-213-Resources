/*
 * IMPLEMENTED BY: ASHWIN ABRAHAM
 */

#include "sort.h"
#include <iostream>

static inline void swap(Journey& j1, Journey& j2)
{
    Journey temp = j1;
    j1 = j2;
    j2 = temp;
}

Journey* (*SorterTree::choices[3])(Journey*, int, int) = { choose_one, choose_two, choose_three };

// Code up the functions defined in sort.cpp

SorterTree::SorterTree(int choice, int l): choice(choice), l(l), comparisons(0), array(new Journey[6]), tree(nullptr), alloc_len(2) {}

SorterTree::~SorterTree()
{
    delete [] array;
}

void SorterTree::insert(int JourneyCode, int price)
{
    if(l == alloc_len)
    {
        alloc_len *= 2;
        Journey* temp = new Journey [alloc_len];
        for(int i = 0; i<l; ++i)
        {
            temp[i] = array[i];
        }
        delete [] array;
        array = temp;
    }
    array[l] = Journey(JourneyCode, price);
    ++l;
}

bool SorterTree::Quicksort(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting

    static int recursion_level = 0;

    if(start > finish || start < 0 || finish >= l)
    {
        if(recursion_level == 0)
        {
            std::cout << comparisons << '\n';
            printArray();
        }
        return false;
    }

    if(start == finish)
    {
        if(recursion_level == 0)
        {
            std::cout << comparisons << '\n';
            printArray();
        }
        return true;
    }

    if(finish - start == 1)
    {
        if(array[start].getJourneyCode() < array[finish].getJourneyCode())
        {
            if(recursion_level == 0)
            {
                std::cout << comparisons << '\n';
                printArray();
            }
            return true;
        }
        swap(array[start], array[finish]);
        ++comparisons;
        if(recursion_level == 0)
        {
            std::cout << comparisons << '\n';
            printArray();
        }
        return true;
    }

    int mindex = start, maxdex = start;
    for(int i = start; i<=finish; ++i)
    {
        if(array[i].getJourneyCode() < array[mindex].getJourneyCode()) mindex = i;
        if(array[i].getJourneyCode() > array[maxdex].getJourneyCode()) maxdex = i;
        comparisons += 2;
    }
    int min_JC = array[mindex].getJourneyCode(), max_JC = array[maxdex].getJourneyCode();
    if(min_JC == max_JC)
    {
        if(recursion_level == 0)
        {
            std::cout << comparisons << '\n';
            printArray();
        }
        return true;
    }

    Journey* pivot = choices[choice-1](array, start, finish);
    if(pivot == nullptr)
    {
        if(recursion_level == 0)
        {
            std::cout << comparisons << '\n';
            printArray();
        }
        return false;
    }
    comparisons += 2;
    if(pivot->getJourneyCode() > max_JC || pivot->getJourneyCode() < min_JC)
    {
        if(recursion_level == 0)
        {
            std::cout << comparisons << '\n';
            printArray();
        }
        return false;
    }

    if(pivot->getJourneyCode() == max_JC)
    {
        swap(array[maxdex], array[finish]);
        ++recursion_level;
        Quicksort(start, finish-1);
        --recursion_level;

        if(recursion_level == 0)
        {
            std::cout << comparisons << '\n';
            printArray();
        }
        return true;
    }

    int p1 = start, p2 = finish;
    while(p1 <= p2)
    {
        /*if(array[p1].getJourneyCode() <= pivot->getJourneyCode() && array[p2].getJourneyCode() > pivot->getJourneyCode())
        {
            ++p1;
            --p2;
            continue;
        }
        if(array[p1].getJourneyCode() > pivot->getJourneyCode() && array[p2].getJourneyCode() <= pivot->getJourneyCode())
        {
            swap(array[p1], array[p2]);
            ++p1;
            --p2;
            continue;
        }
        if(array[p1].getJourneyCode() > pivot->getJourneyCode() && array[p2].getJourneyCode() > pivot->getJourneyCode())
        {
            --p2;
            continue;
        }
        if(array[p1].getJourneyCode() <= pivot->getJourneyCode() && array[p2].getJourneyCode() <= pivot->getJourneyCode())
        {
            ++p1;
            continue;
        }*/
        // these two are the same

        if(array[p1].getJourneyCode() <= pivot->getJourneyCode())
        {
            if(array[p2].getJourneyCode() > pivot->getJourneyCode())
            {
                --p2;
            }
            ++p1;
        }
        else
        {
            if(array[p2].getJourneyCode() <= pivot->getJourneyCode())
            {
                swap(array[p1], array[p2]);
                ++p1;
            }
            --p2;
        }
        comparisons += 2;
    }
    ++recursion_level;
    Quicksort(start, p2);
    Quicksort(p1, finish);
    --recursion_level;
    if(recursion_level == 0)
    {
        std::cout << comparisons << std::endl;
        printArray();
    }
    return true;
}

bool SorterTree::QuicksortWithBSTInsert(int start, int finish)
{
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting
    // Insert chosen pivot into the tree appropriately
    
    // Call appropriate pivot function based on choice
    // Split into 2 parts based on pivot choice
    // Recursively keep sorting

    static int recursion_level = 0;

    if(start > finish || start < 0 || finish >= l)
    {
        if(recursion_level == 0)
        {
            std::cout << comparisons << '\n';
            printArray();
            if(tree != nullptr)
            {
                std::cout << "Imbalance: " << tree->getImbalance() << '\n';
                tree->printBST("");
            }
        }
        return false;
    }

    if(start == finish)
    {
        insertPivot(array[start].getJourneyCode(), array[start].getPrice());
        if(recursion_level == 0)
        {
            std::cout << comparisons << '\n';
            printArray();
            if(tree != nullptr)
            {
                std::cout << "Imbalance: " << tree->getImbalance() << '\n';
                tree->printBST("");
            }
        }
        return true;
    }

    if(finish - start == 1)
    {
        if(array[start].getJourneyCode() < array[finish].getJourneyCode())
        {
            if(recursion_level == 0)
            {
                std::cout << comparisons << '\n';
                printArray();
                if(tree != nullptr)
                {
                    std::cout << "Imbalance: " << tree->getImbalance() << '\n';
                    tree->printBST("");
                }
            }
            return true;
        }
        swap(array[start], array[finish]);
        insertPivot(array[start].getJourneyCode(), array[start].getPrice());
        insertPivot(array[finish].getJourneyCode(), array[finish].getPrice());
        ++comparisons;
        if(recursion_level == 0)
        {
            std::cout << comparisons << '\n';
            printArray();
            if(tree != nullptr)
            {
                std::cout << "Imbalance: " << tree->getImbalance() << '\n';
                tree->printBST("");
            }
        }
        return true;
    }

    int mindex = start, maxdex = start;
    for(int i = start; i<=finish; ++i)
    {
        if(array[i].getJourneyCode() < array[mindex].getJourneyCode()) mindex = i;
        if(array[i].getJourneyCode() > array[maxdex].getJourneyCode()) maxdex = i;
        comparisons += 2;
    }
    int min_JC = array[mindex].getJourneyCode(), max_JC = array[maxdex].getJourneyCode();
    if(min_JC == max_JC)
    {
        for(int i = start; i<=finish; ++i) insertPivot(array[i].getJourneyCode(), array[i].getPrice());
        if(recursion_level == 0)
        {
            std::cout << comparisons << '\n';
            printArray();
            if(tree != nullptr)
            {
                std::cout << "Imbalance: " << tree->getImbalance() << '\n';
                tree->printBST("");
            }
        }
        return true;
    }

    Journey* pivot = choices[choice-1](array, start, finish);
    if(pivot == nullptr)
    {
        if(recursion_level == 0)
        {
            std::cout << comparisons << '\n';
            printArray();
            if(tree != nullptr)
            {
                std::cout << "Imbalance: " << tree->getImbalance() << '\n';
                tree->printBST("");
            }
        }
        return false;
    }
    comparisons += 2;
    if(pivot->getJourneyCode() > max_JC || pivot->getJourneyCode() < min_JC)
    {
        if(recursion_level == 0)
        {
            std::cout << comparisons << '\n';
            printArray();
            if(tree != nullptr)
            {
                std::cout << "Imbalance: " << tree->getImbalance() << '\n';
                tree->printBST("");
            }
        }
        return false;
    }

    insertPivot(pivot->getJourneyCode(), pivot->getPrice());

    if(pivot->getJourneyCode() == max_JC)
    {
        insertPivot(array[finish].getJourneyCode(), array[finish].getPrice());
        swap(array[maxdex], array[finish]);
        ++recursion_level;
        QuicksortWithBSTInsert(start, finish-1);
        --recursion_level;

        if(recursion_level == 0)
        {
            std::cout << comparisons << '\n';
            printArray();
            if(tree != nullptr)
            {
                std::cout << "Imbalance: " << tree->getImbalance() << '\n';
                tree->printBST("");
            }
        }
        return true;
    }

    int p1 = start, p2 = finish;
    while(p1 <= p2)
    {
        /*if(array[p1].getJourneyCode() <= pivot->getJourneyCode() && array[p2].getJourneyCode() > pivot->getJourneyCode())
        {
            ++p1;
            --p2;
            continue;
        }
        if(array[p1].getJourneyCode() > pivot->getJourneyCode() && array[p2].getJourneyCode() <= pivot->getJourneyCode())
        {
            swap(array[p1], array[p2]);
            ++p1;
            --p2;
            continue;
        }
        if(array[p1].getJourneyCode() > pivot->getJourneyCode() && array[p2].getJourneyCode() > pivot->getJourneyCode())
        {
            --p2;
            continue;
        }
        if(array[p1].getJourneyCode() <= pivot->getJourneyCode() && array[p2].getJourneyCode() <= pivot->getJourneyCode())
        {
            ++p1;
            continue;
        }*/

        // these two are the same

        if(array[p1].getJourneyCode() <= pivot->getJourneyCode())
        {
            if(array[p2].getJourneyCode() > pivot->getJourneyCode())
            {
                --p2;
            }
            ++p1;
        }
        else
        {
            if(array[p2].getJourneyCode() <= pivot->getJourneyCode())
            {
                swap(array[p1], array[p2]);
                ++p1;
            }
            --p2;
        }
        comparisons += 2;
    }
    ++recursion_level;
    QuicksortWithBSTInsert(start, p2);
    QuicksortWithBSTInsert(p1, finish);
    --recursion_level;
    if(recursion_level == 0)
    {
        std::cout << comparisons << std::endl;
        printArray();
        if(tree != nullptr)
        {
            std::cout << "Imbalance: " << tree->getImbalance() << '\n';
            tree->printBST("");
        }  
    }
    return true;
}

bool SorterTree::printArray()
{
    for (int i = 0; i < l; i++)
    {
        std::cout<<"Journey code: "<<array[i].getJourneyCode()<<" Journey Price:"<<array[i].getPrice()<<'\n';
    }
    return true;
}

BST* SorterTree::getTree()
{
    return tree;
}

bool SorterTree::insertPivot(int JourneyCode, int price)
{
    if(tree == nullptr) tree = new BST;
    return tree->insert(JourneyCode, price);    
}