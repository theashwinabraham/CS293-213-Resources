/*
 * IMPLEMENTED BY: ASHWIN ABRAHAM
 */

#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

// template <typename T>
// listOfObjects<T>* append(const listOfObjects<T>liconst T& obj)
// {

// }

// listOfObjects<listOfObjects<TrainInfoPerStation*>*>* doBFS(const StationAdjacencyList* adjM, int dest_ind, bool* visited_arr, listOfObjects<int>* to_be_checked, listOfObjects<TrainInfoPerStation*>* curr_list)
// {
//     // static listOfObjects<listOfObjects<TrainInfoPerStation*>*>* list = nullptr;
//     // static listOfObjects<listOfObjects<TrainInfoPerStation*>*>* end_of_list = nullptr;
//     // if(src_ind == dest_ind)
//     // {
//     //     if(list == nullptr)
//     //     {
//     //         list = new listOfObjects<listOfObjects<TrainInfoPerStation*>*>(curr_list);
//     //         end_of_list = list;
//     //     }
//     //     else
//     //     {
//     //         end_of_list->next = curr_list;
//     //         end_of_list = curr_list;
//     //     }
//     // }

//     listOfObjects<int>* next_to_be_checked = nullptr;
//     listOfObjects<int>* ender = nullptr;
//     for(listOfObjects<int>* ind = to_be_checked; ind != nullptr; ind = ind->next)
//     {
//         for(listOfObjects<StationConnectionInfo *> *ptr = adjM[ind->object].toStations; ptr != nullptr; ptr = ptr->next)
//         {
//             if(!visited_arr[ptr->object->adjacentStnIndex])
//             {
//                 visited_arr[ptr->object->adjacentStnIndex] = true;
//                 if(next_to_be_checked == nullptr)
//                 {
//                     next_to_be_checked = new listOfObjects<int>(ptr->object->adjacentStnIndex);
//                     ender = next_to_be_checked;
//                 }
//                 else
//                 {
//                     ender->next = new listOfObjects<int>(ptr->object->adjacentStnIndex);
//                     ender = ender->next;
//                 }
//                 if()
//             }
//         }
//     }
// }

listOfObjects<listOfObjects<int>*>* doBFS(const StationAdjacencyList* adjM, int srcindex, int destindex)
{
    listOfObjects<listOfObjects<int>*>* ret_val = nullptr;
    listOfObjects<listOfObjects<int>*>* paths = new listOfObjects<listOfObjects<int>*>(new listOfObjects<int>(srcindex));
    while(paths != nullptr)
    {
        listOfObjects<int>* last = paths->object;
        for(; last->next != nullptr; last = last->next);
        if(last->object == destindex)
        {
            if(ret_val == nullptr)
            {
                ret_val = new listOfObjects<listOfObjects<int>*>(paths->object);
            }
            else
            {
                listOfObjects<listOfObjects<int>*>* end = ret_val;
                for(; end->next != nullptr; end = end->next);
                end->next = new listOfObjects<listOfObjects<int>*>(paths->object);
            }
        }
        else
        {
            for(listOfObjects<StationConnectionInfo*>* ptr = adjM[last->object].toStations; ptr != nullptr; ptr = ptr->next)
            {
                bool is_present = false;
                //for(listOfObjects<int>* lptr = last; lptr != nullptr; lptr = ptr->next)
                for(listOfObjects<int>* lptr = paths->object; lptr != nullptr; lptr = lptr->next)
                {
                    if(lptr->object == ptr->object->adjacentStnIndex)
                    {
                        is_present = true;
                        break;
                    }
                }
                if(!is_present)
                {
                    listOfObjects<int>* new_path = nullptr;
                    listOfObjects<int>* ender = nullptr;
                    for(listOfObjects<int>* ptr = paths->object; ptr != nullptr; ptr = ptr->next)
                    {
                        if(new_path == nullptr)
                        {
                            new_path = new listOfObjects<int>(ptr->object);
                            ender = new_path;
                        }
                        else
                        {
                            ender->next = new listOfObjects<int>(ptr->object);
                            ender = ender->next;
                        }
                    }
                    ender->next = new listOfObjects<int>(ptr->object->adjacentStnIndex);
                    listOfObjects<listOfObjects<int>*>* my_ptr = paths;
                    for(; my_ptr->next != nullptr; my_ptr = my_ptr->next);
                    my_ptr->next = new listOfObjects<listOfObjects<int>*>(new_path);
                }
            }
        }
        paths = paths->next;
    }
    return ret_val;
}

void Planner::printDirectJourneys(string srcStnName, string destStnName)
{

    // insert your code here

    // Get the list of journeys as a listOfObjects<TrainInfoPerStation *>
    // for the source station and then we can print it out by invoking
    // printStationInfo that we had used in Lab 7.
    // printStationInfo is a private member function of the Planner class
    // It is declared in planner.h and implemented in planner.cpp
    int srcIndex = stnNameToIndex.get(srcStnName)->value;
    int destIndex = stnNameToIndex.get(destStnName)->value;
    listOfObjects<listOfObjects<int>*>* ptr = doBFS(adjacency, srcIndex, destIndex);
    // listOfObjects<listOfObjects<TrainInfoPerStation*>*>* allowed_paths = nullptr;
    for(listOfObjects<listOfObjects<int>*>* possible_path = ptr; possible_path != nullptr; possible_path = possible_path->next)
    {
        // listOfObjects<int>* allowed_codes = nullptr;
        listOfObjects<TrainInfoPerStation*>* allowed_paths = nullptr;
        for(listOfObjects<int>* my_ptr = possible_path->object; my_ptr->next != nullptr; my_ptr = my_ptr->next)
        {
            // for(listOfObjects<StationConnectionInfo>* my_myptr = adjacency[my_ptr->object].toStations; my_myptr != nullptr; my_myptr = my_myptr->next)
            // {
            //     listOfObjects<int>* allowed_codes_here = nullptr;
            //     listOfObjects<int>* end1 = nullptr;
            //     listOfObjects<TrainInfoPerStation*>* corr = nullptr;
            //     listOfObjects<TrainInfoPerStation*>* end2 = nullptr;
            //     for(listOfObjects<TrainInfoPerStation*>* jcodes = my_myptr->object.trains; jcodes != nullptr; jcodes = jcodes->next)
            //     {
            //         if(allowed_codes_here == nullptr)
            //         {
            //             allowed_codes_here = new listOfObjects<int>(jcodes->object->journeyCode);
            //             end1 = allowed_codes_here;
            //             corr = new listOfObjects<TrainInfoPerStation*>(jcodes->object);
            //             end2 = corr;
            //         }
            //         else
            //         {
            //             end1->next = new listOfObjects<int>(jcodes->object->journeyCode);
            //             end2->next = new listOfObjects<TrainInfoPerStation*>(jcodes->object);
            //             end1 = end1->next;
            //             end2 = end2->next;
            //         }
            //     }
            //     if(allowed_codes == nullptr)
            //     {
            //         if(my_ptr->object == srcIndex)
            //         {
            //             allowed_codes = allowed_codes_here;
            //             corresponding_paths = corr;
            //         }
            //         else break;
            //     }
            // }
            // done: continue;
            
            listOfObjects<StationConnectionInfo*>* this_ptr = adjacency[my_ptr->object].toStations;
            for(; this_ptr != nullptr; this_ptr = this_ptr->next)
            {
                if(this_ptr->object->adjacentStnIndex == my_ptr->next->object) break;
            }
            if(allowed_paths == nullptr)
            {
                if(my_ptr->object == srcIndex)
                {
                    listOfObjects<TrainInfoPerStation*>* the_end = nullptr;
                    for(listOfObjects<TrainInfoPerStation*>* lmao = this_ptr->object->trains; lmao != nullptr; lmao = lmao->next)
                    {
                        if(allowed_paths == nullptr)
                        {
                            allowed_paths = new listOfObjects<TrainInfoPerStation*>(lmao->object);
                            the_end = allowed_paths;
                        }
                        else
                        {
                            the_end->next = new listOfObjects<TrainInfoPerStation*>(lmao->object);
                            the_end = the_end->next;
                        }
                    }
                }
                else
                {
                    break;
                }
            }
            else
            {
                listOfObjects<TrainInfoPerStation*>* new_allowed_paths = nullptr;
                listOfObjects<TrainInfoPerStation*>* lmao_end = nullptr;
                for(listOfObjects<TrainInfoPerStation*>* lmao_ptr = allowed_paths; lmao_ptr != nullptr; lmao_ptr = lmao_ptr->next)
                {
                    bool is_present = false;
                    for(listOfObjects<TrainInfoPerStation*>* ran_out = this_ptr->object->trains; ran_out != nullptr; ran_out = ran_out->next)
                    {
                        if(lmao_ptr->object->journeyCode == ran_out->object->journeyCode)
                        {
                            is_present = true;
                            break;
                        }
                    }
                    if(is_present)
                    {
                        if(new_allowed_paths == nullptr)
                        {
                            new_allowed_paths = new listOfObjects<TrainInfoPerStation*>(lmao_ptr->object);
                            lmao_end = new_allowed_paths;
                        }
                        else
                        {
                            lmao_end->next = new listOfObjects<TrainInfoPerStation*>(lmao_ptr->object);
                            lmao_end = lmao_end->next;
                        }
                    }
                }
                allowed_paths = new_allowed_paths;
            }
        }
        if(allowed_paths != nullptr) printStationInfo(allowed_paths);
    }
}

#endif
