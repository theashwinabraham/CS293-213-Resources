#include "dictionary.h"
#include <iostream>

/*
 * COMMANDS:
 * ADD <station_one> <start_time> <station_two> <finish_time>
 * QUERY_STATION <station_one> <start_time>
 * QUERY_JOURNEY <station_one> <start_time> <station_two>
 * EXIT
 */

int main()
{
    Dictionary stations; // Key = Station name, Value = Pointer to the Station
    char query[32];
    while (std::cin >> query)
    {
        if (strcmp(query, "ADD") == 0)
        {
            char s1[32], s2[32];
            double t1, t2;

            std::cin >> s1 >> t1 >> s2 >> t2;
            

            Entry *st1 = stations.get(s1);
            Entry *st2 = stations.get(s2);
            Station *St1;
            Station *St2;

            if (st1 == nullptr) // if stations aren't in the dictionary
            {
                St1 = new Station;
                //St1->name = s1;
                strcpy(St1->name, s1);
                if (!stations.put(Entry(s1, St1)))
                {
                    std::cout << "Error: Too many Stations\n";
                    break;
                }
            }
            else
            {
                St1 = st1->value;
            }

            if (st2 == nullptr)
            {
                St2 = new Station;
                //St2->name = s2;
                strcpy(St2->name, s2);
                if (!stations.put(Entry(s2, St2)))
                {
                    std::cout << "Error: Too many Stations\n";
                    break;
                }
            }
            else
            {
                St2 = st2->value;
            }



            St1->departures.QInsert(Pair(St2, t1));
            St2->arrivals.QInsert(Pair(St1, t2));
        }
        else if (strcmp(query, "QUERY_STATION") == 0)
        {
            char s[32];
            double t;
            std::cin >> s >> t;
            Entry *st = stations.get(s);
            if (st == nullptr)
            {
                std::cout << "Error: This station does not exist\n";
                continue;
            }
            bool exists = false;
            for (int i = 0; i<st->value->departures.size(); ++i)
            {
                if (st->value->departures[i].time >= t)
                {
                    exists = true;
                    std::cout << st->value->departures[i].time << ' ' << st->value->departures[i].station->name << '\n';
                }
            }
            if(!exists) std::cout << "Error: There are no such trains\n";
        }
        else if (strcmp(query, "QUERY_JOURNEY") == 0)
        {
            char s1[32], s2[32];
            double t;
            std::cin >> s1 >> t >> s2;
            Entry *St1 = stations.get(s1);
            Entry *St2 = stations.get(s2);
            if (St1 == nullptr || St2 == nullptr)
            {
                std::cout << "Error: one of these stations do not exist\n";
                continue;
            }
            Station *st1 = St1->value;
            Station *st2 = St2->value;
            int idir = -1;
            for (int i = 0; i < st1->departures.size(); ++i)
            {
                if (st1->departures[i].station == st2)
                {
                    if (st1->departures[i].time >= t && idir == -1)
                        idir = i;
                    else if (st1->departures[i].time >= t && st1->departures[i].time < st1->departures[idir].time)
                        idir = i;
                }
            }
            int ind = -1;
            int other_ind = -1;
            for (int i = 0; i < st1->departures.size(); ++i)
            {
                for (int j = 0; j < st1->departures[i].station->departures.size(); ++j)
                {
                    if (st1->departures[i].station->departures[j].station == st2)
                    {
                        if (st1->departures[i].time >= t && ind == -1)
                        {
                            ind = i;
                            other_ind = j;
                        }
                        else if (st1->departures[i].time >= t && st1->departures[i].time < st1->departures[ind].time)
                        {
                            ind = i;
                            other_ind = j;
                        }
                    }
                }
            }
            if (idir >= 0)
            {
                if (ind >= 0)
                {
                    if (st1->departures[ind].time < st1->departures[idir].time)
                    {
                        std::cout << st1->departures[ind].time << ' ' << st1->departures[ind].station->name << ' ' << st1->departures[ind].station->departures[other_ind].time << '\n';
                    }
                    else
                    {
                        std::cout << st1->departures[idir].time << '\n';
                    }
                }
                else
                    std::cout << st1->departures[idir].time << '\n';
            }
            else
            {
                if (ind >= 0)
                    std::cout << st1->departures[ind].time << ' ' << st1->departures[ind].station->name << ' ' << st1->departures[ind].station->departures[other_ind].time << '\n';
                else
                {
                    std::cout << "Error: There exists no such path for the stations and time selected\n";
                    continue;
                }
            }
        }
        else if (strcmp(query, "EXIT") == 0)
            break;
        else
        {
            char garbage[257];
            std::cout << "Error: Invalid Command\n";
            std::cin.getline(garbage, 256);
        }
    }
}