/*
 * IMPLEMENTED BY: ASHWIN ABRAHAM
 */

#ifndef QUICKSORT_CPP
#define QUICKSORT_CPP

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef DICTIONARY_H
#include "dictionary.h"
#endif

#ifndef CODES_H
#include "codes.h"
#endif

// If you are using the updated planner.cpp, then you simply need to
// sort the list of TrainInfoPerStation objects in stnInfoList.  The
// function that calls Quicksort in planner.cpp (i.e. printStationInfo)
// will then automatically pretty-print the sorted list.
//
// USING THE UPDATED planner.cpp FILE IS STRONGLY RECOMMENDED
//
// Notice that there is a variable K in Quicksort that is to be used as
// described in the problem statement in problems_statement.pdf
// Specifically, if the first call to Quicksort has an argument list of
// n TrainInfoPerStation objects, you can't use additional storage space
// for more than n/K TrainInfoPerStation objects overall (across all
// recursive calls), you must implement random choice for pivot (i.e.
// each element in the list being sorted should be equally likely to
// be chosen as pivot), and each call to finding a random pivot
// within the list being sorted must take time within O(K), regardless
// of how long the list to be sorted is.
//
// In the function signature of Quicksort, stnInfoList is a list of
// TrainInfoPerStation objects that is to be sorted. In the updated
// planner.cpp file, this list (unsorted) is already prepared for you,
// and you need to simply ensure that the list is sorted (see note
// below about sorting order) when Quicksort returns.
//
// A note about the sorting order:
//
// The final list should be sorted with respect to day of week (first)
// and departure time within the day (next).  Thus Sun 900 < Sun 1100
// < Mon 800 < Thu 700 < Fri 1200
//
//
// Based on how we saw some of you were trying to approach the problem
// in the lab of Sep 23, we are providing another function QuicksortSimple
// with a slightly extended signature. In addition to the list stnInfoList,
// which is passed as the first argument to QuicksortSimple, there are two
// integer parameters "start" and "end", just like in the usual Quicksort
// of an array (as in Prof. Naveen Garg's lectures, for example).
// How do we interpret these "start" and "end" variables in this case,
// when we are trying to sort a list?
// Well, here is one way of thinking about this: If we start
// counting elements of the list starting from stnInfoList and
// chasing "next" pointers until nullptr is reached, the corresponding
// elements can be thought of as elements of a (virtual) array indexed
// from 0 onwards.
// Then, the call to Quicksort must sort the part of the list
// consisting of elements at indices start, start+1, ... until end
// of the above virtual array.
// The whole point of this assignment is to have you do this without
// converting the whole list to an array.
//
// Remember it is indeed possible to solve this problem using the
// function Quicksort with only stnInfoList as its argument.  However,
// if you are finding it difficult to implement Quicksort, you can
// implement QuicksortSimple instead.  Those who implement both
// Quicksort and QuicksortSimple potentially stand to gain some bonus
// points.

bool less_than(const TrainInfoPerStation* a, const TrainInfoPerStation* b)
{
    int inda = 0, indb = 0;
    for(; !(a->daysOfWeek)[inda]; inda++);
    for(; !(b->daysOfWeek)[indb]; indb++);
    if(inda == indb)
    {
        return a->depTime < b->depTime;
    }
    return inda < indb;
}

void my_quicksort(listOfObjects<TrainInfoPerStation*> *start, listOfObjects<TrainInfoPerStation*> *end, int llim, int rlim, int K, listOfObjects<TrainInfoPerStation*>** arr_ptrs)
{
    if(llim < rlim)
    {
        int pivindex = llim + rand() % (rlim - llim);
        listOfObjects<TrainInfoPerStation*> * pivot = arr_ptrs[pivindex/K];
        for(int i = 0; i<(pivindex % K); ++i)
        {
            pivot = pivot->next;
        }
        int num_less = 0;
        listOfObjects<TrainInfoPerStation*> * curr = start;
        for(listOfObjects<TrainInfoPerStation*> *pos = start; pos != end; pos = pos->next)
        {
            if(less_than(pos->object, pivot->object))
            {
                TrainInfoPerStation* temp = pos->object;
                pos->object = curr->object;
                curr->object = temp;
                if(curr == pivot)
                {
                    pivot = pos;
                }
                curr = curr->next;
                ++num_less;
            }
        }
        TrainInfoPerStation* temp = pivot->object;
        pivot->object = curr->object;
        curr->object = temp;
        my_quicksort(start, curr, llim, llim + num_less, K, arr_ptrs);
        my_quicksort(curr->next, end, llim + num_less + 1, rlim, K, arr_ptrs);
    }
}


void Planner::Quicksort(listOfObjects<TrainInfoPerStation *> *stnInfoList)
{
    // A few static variable declarations
    static int K = 4;               // Parameter to be experimented with
    /*static int recursionLevel = -1; // This can be used to find out at which
                                    // level of the recursion you are in
    static listOfObjects<TrainInfoPerStation*>** arr_ptrs = nullptr;
    static listOfObjects<TrainInfoPerStation*> *lptr, *rptr; // at any point in quicksort, the part of the list we are concerned with has
    // pos >= lptr and < rptr
    static int llim, rlim; // indices of lptr and rptr
    // Increment recursion level on entering the function
    recursionLevel++;

    // If you need to set up additional storage (upto n/K TrainInfoPerStation
    // elements), it's ok to do it *once* using static variables/array.
    // Using the static recursionLevel, you can ensure that the storage
    // allocation is done only the first time Quicksort is called, and not
    // in every recursive call.
    //
    // Note that if you allocate space for upto n/K TrainInfoPerStation in
    // each recursive call, you will end up using much more than n/K space
    // overall.  So you MUST NOT allocate space in each recursive call.
    //
    // A variable/array defined using static is not created afresh in
    // each recursive call.  Instead, a single copy of it is maintained
    // across all recursions.

    if (recursionLevel == 0)
    {
        // Find length of the list stnInfoList, if needed.
        // Allocate additional space for upto n/K TrainInfoPerStation objects
        // if needed.
        // Do other things that you may want to do only at the beginning
        // as a pre-processing step.
        int N = 0;
        for(listOfObjects<TrainInfoPerStation *> *ptr = stnInfoList; ptr != nullptr; ptr = ptr->next) ++N;
        llim = 0;
        rlim = N;
        lptr = stnInfoList;
        rptr = nullptr;
        arr_ptrs = new listOfObjects<TrainInfoPerStation*>* [(N%K == 0 ? N/K : 1 + N/K)];
        int num = 0;
        for(listOfObjects<TrainInfoPerStation *> *ptr = stnInfoList; ptr != nullptr; ptr = ptr->next, ++num)
        {
            if(num%K == 0)
            {
                arr_ptrs[num/K] = ptr;
            }
        }
    }

    // Put your code for the core of Quicksort here
    if(llim < rlim)
    {
        int pivindex = llim + rand() % (rlim - llim);
        listOfObjects<TrainInfoPerStation*> * pivot = arr_ptrs[pivindex/K];
        for(int i = 0; i<(pivindex % K); ++i)
        {
            pivot = pivot->next;
        }

        int num_less = 0;
        for(listOfObjects<TrainInfoPerStation*> *pos = lptr; pos != rptr; pos = pos->next)
        {

        }
    }

    // Decrement recursion level before leaving the function
    if(recursionLevel == 0)
    {
        delete [] arr_ptrs;
        arr_ptrs = nullptr;
    }
    recursionLevel--;*/

    int N = 0;
    for(listOfObjects<TrainInfoPerStation *> *ptr = stnInfoList; ptr != nullptr; ptr = ptr->next) ++N;
    int llim = 0;
    int rlim = N;
    listOfObjects<TrainInfoPerStation *> *lptr = stnInfoList;
    listOfObjects<TrainInfoPerStation *> *rptr = nullptr;
    listOfObjects<TrainInfoPerStation *> **arr_ptrs = new listOfObjects<TrainInfoPerStation*>* [(N%K == 0 ? N/K : 1 + N/K)];
    int num = 0;
    for(listOfObjects<TrainInfoPerStation *> *ptr = stnInfoList; ptr != nullptr; ptr = ptr->next, ++num)
    {
        if(num%K == 0)
        {
            arr_ptrs[num/K] = ptr;
        }
    }
    my_quicksort(lptr, rptr, llim, rlim, K, arr_ptrs);

    return;
}

void Planner::QuicksortSimple(listOfObjects<TrainInfoPerStation *> *stnInfoList, int start, int end)
{
    // A few static variable declarations
    static int K = 4;               // Parameter to be experimented with
    /*static int recursionLevel = -1; // This can be used to find out at which
                                    // level of the recursion you are in

    // Increment recursion level on entering the function
    recursionLevel++;

    // If you need to set up additional storage (upto n/K TrainInfoPerStation
    // elements), it's ok to do it *once* using static variables/array.
    // Using the static recursionLevel, you can ensure that the storage
    // allocation is done only the first time Quicksort is called, and not
    // in every recursive call.
    //
    // Note that if you allocate space for upto n/K TrainInfoPerStation in
    // each recursive call, you will end up using much more than n/K space
    // overall.  So you MUST NOT allocate space in each recursive call.
    //
    // A variable/array defined using static is not created afresh in
    // each recursive call.  Instead, a single copy of it is maintained
    // across all recursions.

    if (recursionLevel == 0)
    {
        // Allocate additional space for upto n/K TrainInfoPerStation objects
        // if needed.
        // Do other things that you may want to do only at the beginning
        // as a pre-processing step.
    }

    // Put your code for the core of QuicksortSimple here

    // Decrement recursion level before leaving the function
    recursionLevel--;*/
    listOfObjects<TrainInfoPerStation *> * start_ptr = stnInfoList;
    for(int i = 0; i<start; ++i) start_ptr = start_ptr->next;
    listOfObjects<TrainInfoPerStation *> * end_ptr = stnInfoList;
    for(int i = 0; i<end; ++i) end_ptr = end_ptr->next;
    end_ptr = end_ptr->next;
    int N = 0;
    for(listOfObjects<TrainInfoPerStation *> *ptr = start_ptr; ptr != end_ptr; ptr = ptr->next) ++N;
    int llim = 0;
    int rlim = N;
    listOfObjects<TrainInfoPerStation *> *lptr = start_ptr;
    listOfObjects<TrainInfoPerStation *> *rptr = end_ptr;
    listOfObjects<TrainInfoPerStation *> **arr_ptrs = new listOfObjects<TrainInfoPerStation*>* [(N%K == 0 ? N/K : 1 + N/K)];
    int num = 0;
    for(listOfObjects<TrainInfoPerStation *> *ptr = start_ptr; ptr != end_ptr; ptr = ptr->next, ++num)
    {
        if(num%K == 0)
        {
            arr_ptrs[num/K] = ptr;
        }
    }
    my_quicksort(lptr, rptr, llim, rlim, K, arr_ptrs);

    return;
}




#endif
