#ifndef CHOOSE_H
#define CHOOSE_H
// The following 4 are functions whose functionality has been hidden.
// You have been provided the compiled .o file (choose.o) for the same
// Link it while compiling your code to use the following functions

// x is the pointer to the array, start is the starting index and finish is the last index, 
// Please ensure start <= finish, start >= 0 and finish <= N-1

#include "journey.h"

Journey* choose_one(Journey* x, int start, int finish); 
Journey* choose_two(Journey* x, int start, int finish);
Journey* choose_three(Journey* x, int start, int finish);

#endif