#include <cstdlib>
#include <iostream>
#include <cassert>
#include <chrono>
#include "sort.h"


using namespace std;

int main(int argc, char** argv)
{
    if(argc != 3)
    {
        cout<< argc << ": Incorrect number of arguments"<<endl;
        exit(0);
    }

    int num_entries = atoi(argv[1]); // Number of journeys to enter
    int pivot_chooser = atoi(argv[2]); // Function to be used for choosing pivot

    assert(1<=pivot_chooser && pivot_chooser<=4); // Valid choice of pivot chooser function
    
    // Write your code here to accept input of journeys, input one per line as a (code, price) pair
    // Also write code here to obtain different inputs as in the various parts of the question
    // Add functionality to time your code (chrono may be helpful here)


    SorterTree s_normal(pivot_chooser, 0), s_BST(pivot_chooser, 0);
    for(int i = 0; i<num_entries; ++i)
    {
        int jc, p;
        std::cin >> jc >> p;
        s_normal.insert(jc, p);
        s_BST.insert(jc, p);
    }
    auto start = std::chrono::steady_clock::now();
    s_BST.QuicksortWithBSTInsert(0, num_entries - 1);
    auto stop = std::chrono::steady_clock::now();
    std::cout << "Quicksort with BST: " << std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count() << '\n';
    auto new_start = std::chrono::steady_clock::now();
    s_normal.Quicksort(0, num_entries-1);
    auto new_stop = std::chrono::steady_clock::now();
    std::cout << "Quicksort without BST: " << std::chrono::duration_cast<std::chrono::microseconds>(new_stop - new_start).count() << '\n';
    std::flush(std::cout);
}
