#ifndef PLANNER_H
#define PLANNER_H

#include <iostream>
#include "queue.h"
#include "circularQueue.cpp"

struct Pair {
    struct Station* station;
    double time;

    Pair(): station(nullptr) {}

    Pair(Station* st, double t): station(st), time(t) {}
};

struct Station {
    // define suitable fields here

    char name[32]; // Name of the Station

    DynamicQueue<Pair> departures; // Pair of (pointer to next station, time of leaving current station)
    DynamicQueue<Pair> arrivals; // Pair of (pointer to station coming from, time of arrival)
};

/*struct Journey {
    // define suitable fields here
    struct Station* begin;
    struct Station* end;
    double start_time;
    double end_time;
};

struct Query {
    // define suitable fields here
};

struct Planner {
    // define suitable fields here
    Dictionary stations;
};*/

#endif