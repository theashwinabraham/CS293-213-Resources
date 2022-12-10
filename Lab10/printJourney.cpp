/*
 * IMPLEMENTED BY: ASHWIN ABRAHAM
 */

#ifndef PRINT_JOURNEY_CPP
#define PRINT_JOURNEY_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#include "planner.h"
#include "dictionary.h"

using namespace std;

struct InfoStr
{
    int JourneyCode;
    std::string start;
    std::string end;
    int dep_time;
    int arr_time;
};

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

void handle(Planner* this_ptr, void (Planner::*PrintStationInfo)(listOfObjects<TrainInfoPerStation *> *), const StationAdjacencyList* adjacency, Dictionary<int> &stnNameToIndex, listOfObjects<int>* list, int maxStopOvers, int maxTransitTime, listOfObjects<listOfObjects<TrainInfoPerStation*>*>* allowed_paths, listOfObjects<TrainInfoPerStation*>* starter = nullptr, listOfObjects<TrainInfoPerStation*>* ender = nullptr)
{
    if(allowed_paths != nullptr)
    {
        for(listOfObjects<TrainInfoPerStation*>* ptr = allowed_paths->object; ptr != nullptr; ptr = ptr->next)
        {
            listOfObjects<TrainInfoPerStation*>* next_starter;
            listOfObjects<TrainInfoPerStation*>* next_ender;
            if(starter == nullptr)
            {
                next_starter = new listOfObjects<TrainInfoPerStation*>(ptr->object);
                next_ender = next_starter;
            }
            else
            {
                next_starter = starter;
                ender->next = new listOfObjects<TrainInfoPerStation*>(ptr->object);
                next_ender = ender->next;
            }
            handle(this_ptr, PrintStationInfo, adjacency, stnNameToIndex, list, maxStopOvers, maxTransitTime, allowed_paths->next, next_starter, next_ender);
        }
    }
    else
    {
        int num_layovers = 0;
        int max_transit_time = 0;
        int curr_jc = -1;
        listOfObjects<int>* lmao_lmfao = list;
        InfoStr x;
        x.start = stnNameToIndex.getKeyAtIndex(list->object);
        x.dep_time = starter->object->depTime;
        x.JourneyCode = starter->object->journeyCode;
        listOfObjects<InfoStr>* to_print = new listOfObjects<InfoStr>(x);
        listOfObjects<InfoStr>* end_to_print = to_print;
        listOfObjects<TrainInfoPerStation*>* tptr = starter;
        for(; tptr->next != nullptr; tptr = tptr->next, lmao_lmfao = lmao_lmfao->next)
        {
            if(tptr->object->journeyCode != tptr->next->object->journeyCode)
            {
                ++num_layovers;
                listOfObjects<StationConnectionInfo*>* ptr = adjacency[lmao_lmfao->next->object].fromStations;
                end_to_print->object.end = stnNameToIndex.getKeyAtIndex(lmao_lmfao->next->object);
                for(; ptr != nullptr; ptr = ptr->next)
                {
                    if(ptr->object->adjacentStnIndex == lmao_lmfao->object) break;
                }
                listOfObjects<TrainInfoPerStation*>* the_tr = ptr->object->trains;
                for(; the_tr != nullptr; the_tr = the_tr->next)
                {
                    if(the_tr->object->journeyCode == tptr->object->journeyCode) break;
                }
                int arr_time = the_tr->object->arrTime;
                end_to_print->object.arr_time = arr_time;
                int dep_time = tptr->next->object->depTime;
                int td = (dep_time/100 - arr_time/100)*60 + (dep_time%100 - arr_time%100);
                if(arr_time > dep_time) td += 24*60;
                if(td > max_transit_time) max_transit_time = td;
                InfoStr x;
                x.start = end_to_print->object.end;
                x.JourneyCode = tptr->next->object->journeyCode;
                x.dep_time = dep_time;
                end_to_print->next = new listOfObjects<InfoStr>(x);
                end_to_print = end_to_print->next;
            }
        }
        end_to_print->object.end = stnNameToIndex.getKeyAtIndex(lmao_lmfao->next->object);
        listOfObjects<StationConnectionInfo*>* wow_ptr = adjacency[lmao_lmfao->next->object].fromStations;
        for(; wow_ptr != nullptr; wow_ptr = wow_ptr->next)
        {
            if(wow_ptr->object->adjacentStnIndex == lmao_lmfao->object) break;
        }
        listOfObjects<TrainInfoPerStation*>* the_tr = wow_ptr->object->trains;
        for(; the_tr != nullptr; the_tr = the_tr->next)
        {
            if(the_tr->object->journeyCode == tptr->object->journeyCode) break;
        }
        end_to_print->object.arr_time = the_tr->object->arrTime;

        if(num_layovers <= maxStopOvers && max_transit_time <= maxTransitTime*60)
        {
            cout << "\n\n";
            // for(listOfObjects<TrainInfoPerStation*>* ptr_ptr = starter; ptr_ptr != nullptr; ptr_ptr = ptr_ptr->next, list = list->next)
            // {
            //     cout << "TRAIN " << BLUE << ptr_ptr->object->journeyCode << RESET << " FROM " << GREEN << stnNameToIndex.getKeyAtIndex(list->object) << RESET << " TO " << GREEN << stnNameToIndex.getKeyAtIndex(list->next->object) << RESET << " AT " << RED << ptr_ptr->object->depTime << RESET << endl;
            // }
            for(listOfObjects<InfoStr>* lmak_ptr = to_print; lmak_ptr != nullptr; lmak_ptr = lmak_ptr->next)
            {
                cout << "JOURNEY " << BLUE << lmak_ptr->object.JourneyCode << RESET << " FROM " << GREEN << lmak_ptr->object.start << RESET << " TO " << GREEN << lmak_ptr->object.end << RESET << RED << " " << lmak_ptr->object.dep_time << RESET << " - " << RED << lmak_ptr->object.arr_time << RESET << endl;
            }
            cout << "\n\n";
        }
    }
}

/*listOfObjects<listOfObjects<TrainInfoPerStation*>*>*/ void allowed_paths(Planner* lmfao_ptr, void (Planner::*PrintStationInfo)(listOfObjects<TrainInfoPerStation *> *), const StationAdjacencyList* adjacency, Dictionary<int> &stnNameToIndex, int srcIndex, int destIndex, int maxStopOvers, int maxTransitTime, listOfObjects<listOfObjects<int>*>* ptr)
{
    listOfObjects<listOfObjects<TrainInfoPerStation*>*>* ret_val = nullptr;
    listOfObjects<listOfObjects<TrainInfoPerStation*>*>* end_ret_val = nullptr;
    for(listOfObjects<listOfObjects<int>*>* possible_path = ptr; possible_path != nullptr; possible_path = possible_path->next)
    {
        // int stopovers = 0;
        // int transtime = 0;
        listOfObjects<listOfObjects<TrainInfoPerStation*>*>* allowed_paths = nullptr;
        listOfObjects<listOfObjects<TrainInfoPerStation*>*>* end_allowed_paths = nullptr;
        for(listOfObjects<int>* my_ptr = possible_path->object; my_ptr->next != nullptr; my_ptr = my_ptr->next)
        {
            listOfObjects<StationConnectionInfo*>* this_ptr = adjacency[my_ptr->object].toStations;
            for(; this_ptr != nullptr; this_ptr = this_ptr->next)
            {
                if(this_ptr->object->adjacentStnIndex == my_ptr->next->object) break;
            }
            if(allowed_paths == nullptr)
            {
                if(my_ptr->object == srcIndex)
                {
                    // listOfObjects<TrainInfoPerStation*>* the_end = nullptr;
                    // for(listOfObjects<TrainInfoPerStation*>* lmao = this_ptr->object->trains; lmao != nullptr; lmao = lmao->next)
                    // {
                    //     if(allowed_paths == nullptr)
                    //     {
                    //         allowed_paths = new listOfObjects<TrainInfoPerStation*>(lmao->object);
                    //         the_end = allowed_paths;
                    //     }
                    //     else
                    //     {
                    //         the_end->next = new listOfObjects<TrainInfoPerStation*>(lmao->object);
                    //         the_end = the_end->next;
                    //     }
                    // }
                    allowed_paths = new listOfObjects<listOfObjects<TrainInfoPerStation*>*>(this_ptr->object->trains);
                    end_allowed_paths = allowed_paths;
                }
                else
                {
                    abort();
                }
            }
            else
            {
                // listOfObjects<TrainInfoPerStation*>* new_allowed_paths = nullptr;
                // listOfObjects<TrainInfoPerStation*>* lmao_end = nullptr;
                // for(listOfObjects<TrainInfoPerStation*>* lmao_ptr = allowed_paths; lmao_ptr != nullptr; lmao_ptr = lmao_ptr->next)
                // {
                //     bool is_present = false;
                //     for(listOfObjects<TrainInfoPerStation*>* ran_out = this_ptr->object->trains; ran_out != nullptr; ran_out = ran_out->next)
                //     {
                //         if(lmao_ptr->object->journeyCode == ran_out->object->journeyCode)
                //         {
                //             is_present = true;
                //             break;
                //         }
                //     }
                //     if(is_present)
                //     {
                //         if(new_allowed_paths == nullptr)
                //         {
                //             new_allowed_paths = new listOfObjects<TrainInfoPerStation*>(lmao_ptr->object);
                //             lmao_end = new_allowed_paths;
                //         }
                //         else
                //         {
                //             lmao_end->next = new listOfObjects<TrainInfoPerStation*>(lmao_ptr->object);
                //             lmao_end = lmao_end->next;
                //         }
                //     }
                // }
                // allowed_paths = new_allowed_paths;
                end_allowed_paths->next = new listOfObjects<listOfObjects<TrainInfoPerStation*>*>(this_ptr->object->trains);
                end_allowed_paths = end_allowed_paths->next;
            }
        }
        handle(lmfao_ptr, PrintStationInfo, adjacency, stnNameToIndex, possible_path->object, maxStopOvers, maxTransitTime, allowed_paths);
    }
}


void Planner::printPlanJourneys(string srcStnName, string destStnName, int maxStopOvers, int maxTransitTime)
{

    // insert your code here

    int srcIndex = stnNameToIndex.get(srcStnName)->value;
    int destIndex = stnNameToIndex.get(destStnName)->value;
    // listOfObjects<listOfObjects<int>*>* ptr = doBFS(adjacency, srcIndex, destIndex);

    allowed_paths(this, &Planner::printStationInfo, adjacency, stnNameToIndex, srcIndex, destIndex, maxStopOvers, maxTransitTime, doBFS(adjacency, srcIndex, destIndex));

    // Whenever you need to print a journey, construct a
    // listOfObjects<TrainInfoPerStation *> appropriately, and then
    // use printStationInfo that we had used in Lab 7.
    // printStationInfo is a private member function of
    // the Planner class. It is declared in planner.h and implemented in
    // planner.cpp

    return;
}

#endif
