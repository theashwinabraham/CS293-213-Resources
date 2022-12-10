/*
 * AUTHOR: ASHWIN ABRAHAM
 */

#include <iostream>
#include <fstream>
#include "helper.h"
// using namespace std;

struct Node {
    List<unsigned int> out_edges;
    List<unsigned int> in_edges;
};

struct UNode {
    List<unsigned int> edges;
};

void DFS(UNode* sim_nodes, Node* nodes, bool* visited, int* collapsed, List<unsigned int>* others, int numNodes, int start = 0)
{
    static int recursion_level = 0;
    static int max = -1;
    static List<unsigned int> other_nodes;
    static List<unsigned int> deez_nuts;
    if(start > max) max = start;
    visited[start] = true;
    // bool node_is = false;
    // for(ListObject<unsigned int> *ptr = deez_nuts.head; ptr != nullptr; ptr = ptr->next)
    // {
    //     if(ptr->obj == start)
    //     {
    //         node_is = true;
    //         break;
    //     }
    // }
    // if(!node_is)
    // {
    //     deez_nuts.
    // }
    deez_nuts.insert(start);

    for(ListObject<unsigned int>* ptr = nodes[start].out_edges.head; ptr != nullptr; ptr = ptr->next)
    {
        bool exists = false;
        for(ListObject<unsigned int> *qtr = other_nodes.head; qtr != nullptr; qtr = qtr->next)
        {
            if(qtr->obj == ptr->obj)
            {
                exists = true;
                break;
            }
        }
        if(!exists)
        {
            other_nodes.insert(ptr->obj);
        }
    }

    for(ListObject<unsigned int> *ptr = sim_nodes[start].edges.head; ptr != nullptr; ptr = ptr->next)
    {
        if(!visited[ptr->obj])
        {
            ++recursion_level;
            DFS(sim_nodes, nodes, visited, collapsed, others, numNodes, ptr->obj);
            --recursion_level;
        }
    }

    if(recursion_level == 0)
    {
        for(ListObject<unsigned int> *ptr = deez_nuts.head; ptr != nullptr; ptr = ptr->next)
        {
            collapsed[ptr->obj] = max;
            others[ptr->obj] = other_nodes;
        }
        max = -1;
        deez_nuts = List<unsigned int>();
        other_nodes = List<unsigned int>();
        for(int i = 0; i<numNodes; ++i)
        {
            if(!visited[i])
            {
                DFS(sim_nodes, nodes, visited, collapsed, others, numNodes, i);
                break;
            }
        }
    }
}

Node* nodes, *sim_nodes;
bool similiarity(int n1, int n2)
{
    for(ListObject<unsigned int>* ptr = sim_nodes[n1].out_edges.head; ptr != nullptr; ptr = ptr->next)
    {
        if(ptr->obj == n2)
        {
            return true;
        }
    }
    if(nodes[n1].in_edges.size == 1 && nodes[n1].in_edges.head->obj == n2)
    {
        sim_nodes[n1].out_edges.insert(n2);
        sim_nodes[n2].in_edges.insert(n1);
        return true;
    }
    if(nodes[n1].in_edges.size > 0 && nodes[n2].in_edges.size > 0)
    {
        bool every_a = true, every_b = true;
        for(ListObject<unsigned int> *ptr = nodes[n1].in_edges.head; ptr != nullptr; ptr = ptr->next)
        {
            bool exists = false;
            for(ListObject<unsigned int> *qtr = nodes[n2].in_edges.head; qtr != nullptr; qtr = qtr->next)
            {
                if(similiarity(ptr->obj, qtr->obj))
                {
                    exists = true;
                    break;
                }
            }
            if(!exists)
            {
                every_a = false;
                break;
            }
        }
        for(ListObject<unsigned int> *ptr = nodes[n2].in_edges.head; ptr != nullptr; ptr = ptr->next)
        {
            bool exists = false;
            for(ListObject<unsigned int> *qtr = nodes[n1].in_edges.head; qtr != nullptr; qtr = qtr->next)
            {
                if(similiarity(ptr->obj, qtr->obj))
                {
                    exists = true;
                    break;
                }
            }
            if(!exists)
            {
                every_b = false;
                break;
            }
        }
        if(every_a && every_b)
        {
            sim_nodes[n1].out_edges.insert(n2);
            sim_nodes[n2].in_edges.insert(n1);
            sim_nodes[n2].out_edges.insert(n1);
            sim_nodes[n1].in_edges.insert(n2);
            return true;
        }
    }
    return false;
}

int main()
{
    // ios::sync_with_stdio(false);
    // cin.tie(0);
    std::ofstream out("outgraph.txt");


    int numNodes;
    std::cin >> numNodes;

    nodes = new Node[numNodes];
    sim_nodes = new Node[numNodes];
    int start, dest;
    while(std::cin >> start >> dest)
    {
        if(start == -1 || dest == -1) break;
        nodes[start - 1].out_edges.insert(dest - 1);
        nodes[dest - 1].in_edges.insert(start - 1);
    }
    out << "Source Nodes: ";
    bool started = false;
    for(int i = 0; i<numNodes; ++i)
    {
        if(nodes[i].in_edges.size == 0)
        {
            if(started)
            {
                out << ' ';
            }
            out << i+1;
            started = true;
        }
    }
    out << "\n\n";
    int sim1, sim2;
    // List<Pair> sims;
    while(std::cin >> sim1 >> sim2)
    {
        if(sim1 == -1 || sim2 == -1) break;
        if(nodes[sim1 - 1].in_edges.size == 0 && nodes[sim2 - 1].in_edges.size == 0)
        {
            sim_nodes[sim1 - 1].out_edges.insert(sim2 - 1);
            sim_nodes[sim2 - 1].in_edges.insert(sim1 - 1);
        }
    }

    for(int i = 0; i<numNodes; ++i)
    {
        for(int j = 0; j<numNodes; ++j)
        {
            similiarity(i, j);
        }
    }
    out << "Similiar Node Pairs:";
    for(int i = 0; i<numNodes; ++i)
    {
        for(ListObject<unsigned int> *ptr = sim_nodes[i].out_edges.head; ptr != nullptr; ptr = ptr->next)
        {
            out << " (" << i+1 << ", " << ptr->obj + 1 << ")";
        }
    }
    out << "\n\n";
    bool* visited = new bool[numNodes];
    int* collapsed = new int[numNodes];
    List<unsigned int>* others = new List<unsigned int>[numNodes];
    for(int i = 0; i<numNodes; ++i)
    {
        visited[i] = false;
        collapsed[i] = -1;
    }

    UNode* SimNodes = new UNode[numNodes];
    for(int i = 0; i<numNodes; ++i)
    {
        for(ListObject<unsigned int> *ptr = sim_nodes[i].out_edges.head; ptr != nullptr; ptr = ptr->next)
        {
            SimNodes[i].edges.insert(ptr->obj);
            SimNodes[ptr->obj].edges.insert(i);
        }
    }

    DFS(SimNodes, nodes, visited, collapsed, others, numNodes);

    List<unsigned int> done;
    List<List<unsigned int> > ur_mom;
    List<Pair> edges;
    for(int i = 0; i<numNodes; ++i)
    {
        bool is_done = false;
        for(ListObject<unsigned int> *ptr = done.head; ptr != nullptr; ptr = ptr->next)
        {
            if(ptr->obj == collapsed[i])
            {
                is_done = true;
                break;
            }
        }
        if(!is_done)
        {
            done.insert(collapsed[i]);
            List<unsigned int> l = List<unsigned int>();
            for(ListObject<unsigned int> *ptr = others[i].head; ptr != nullptr; ptr = ptr->next)
            {
                bool is_there = false;
                for(ListObject<unsigned int> *qtr = l.head; qtr != nullptr; qtr = qtr->next)
                {
                    if(qtr->obj == collapsed[ptr->obj])
                    {
                        is_there = true;
                        break;
                    }
                }
                if(!is_there)
                {
                    l.insert(collapsed[ptr->obj]);
                    if(collapsed[i] != collapsed[ptr->obj]) edges.insert(Pair(collapsed[i], collapsed[ptr->obj]));
                }
            }
            ur_mom.insert(l);
        }
    }

    out << "Collapsed Graph:\n" << done.size << ':';
    for(ListObject<unsigned int> *wtr = done.head; wtr != nullptr; wtr = wtr->next)
    {
        out << ' ' << 1+wtr->obj;
    }
    out << '\n';
    for(ListObject<Pair> *ptr = edges.head; ptr != nullptr; ptr = ptr->next)
    {
        out << 1+ptr->obj.x << ' ' << 1+ptr->obj.y << '\n';
    }
}