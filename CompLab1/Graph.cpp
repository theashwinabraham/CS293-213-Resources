/*
 * IMPLEMENTED BY: ASHWIN ABRAHAM
 */

#ifndef GRAPH_BST_CPP
#define GRAPH_BST_CPP

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

#ifndef GRAPH_BST_H
#include "Graph.h"
#endif

// Add code as appropriate for your implementation
void Graph::modifiedDFS(int start)
{
    static int recursion_level = 0;
    if(numNodes == 0) return;
    if(recursion_level == 0)
    {
        ++num_connected;
        if(bsts == nullptr)
        {
            bsts = new List<BST*>(new BST);
        }
        else
        {
            List<BST*> *obst = bsts;
            bsts = new List<BST*>(new BST);
            bsts->next = obst;
        }
    }

    ++visit_count[start];
    bsts->obj->insert(start+1);

    List<int>* do_later = nullptr;
    for(List<Pair>* neighbour = nodes[start].neighbours; neighbour != nullptr; neighbour = neighbour->next)
    {
        if(neighbour->obj.allowed)
        {
            // std::cout << "LMAO " << start << ' ' << neighbour->obj.val << std::endl; 
            if(visit_count[neighbour->obj.val] == 0)
            {
                parents[neighbour->obj.val] = start;
                for(List<Pair>* ptr = nodes[neighbour->obj.val].neighbours; ptr != nullptr; ptr = ptr->next)
                {
                    if(ptr->obj.val == start)
                    {
                        ptr->obj.allowed = false;
                        break;
                    }
                }
                ++recursion_level;
                modifiedDFS(neighbour->obj.val);
                --recursion_level;
            }
            else
            {
                if(visit_count[neighbour->obj.val] == 1)
                {
                    for(List<Pair>* ptr = nodes[neighbour->obj.val].neighbours; ptr != nullptr; ptr = ptr->next)
                    {
                        if(ptr->obj.val == start)
                        {
                            ptr->obj.allowed = false;
                            break;
                        }
                    }
                    if(do_later == nullptr)
                    {
                        do_later = new List<int>(neighbour->obj.val);
                    }
                    else
                    {
                        List<int>* ddl = do_later;
                        do_later = new List<int>(neighbour->obj.val);
                        do_later->next = ddl;
                    }
                }
                if(start != parents[neighbour->obj.val])
                {
                    // std::cout << start << ' ' << neighbour->obj.val << '\n';
                    // for(int i = 0; i<numNodes; ++i)
                    // {
                    //     std::cout << parents[i] << " KK" << std::endl;
                    // }
                    for(int x = start; x != neighbour->obj.val; x = parents[x])
                    {
                        // std::cout << x << std::endl;
                        if(x == -1){ break;}            
                        in_cycle[x] = true;
                    }
                    in_cycle[neighbour->obj.val] = true;
                }
            }
        }
    }

    for(List<int>* pptr = do_later; pptr != nullptr; pptr = pptr->next)
    {
        ++recursion_level;
        modifiedDFS(pptr->obj);
        --recursion_level;
    }

    if(recursion_level == 0)
    {
        int next_unv = -1;
        for(int i = 0; i<numNodes; ++i)
        {
            if(visit_count[i] == 0)
            {
                next_unv = i;
                break;
            }
        }
        if(next_unv >= 0)
        {
            modifiedDFS(next_unv);
        }
    }

    return;
}

void Graph::printResults()
{
    std::cout << "Number of connected components: " << num_connected << std::endl;
    int num_once = 0, num_twice = 0;
    for(int i = 0; i<numNodes; ++i)
    {
        if(visit_count[i] == 1) ++num_once;
        if(visit_count[i] == 2) ++num_twice;
    }
    std::cout << "Number of nodes visited exactly once: " << num_once << std::endl;
    std::cout << "Number of nodes visited exactly twice: " << num_twice << std::endl;
    int num_in_cycle = 0;
    for(int i = 0; i<numNodes; ++i)
    {
        if(in_cycle[i]) ++num_in_cycle;
    }
    std::cout << "Number of nodes present in a cycle: " << num_in_cycle << std::endl;
    std::cout << "The Binary Trees generated: " << std::endl;
    for(List<BST*> *pp = bsts; pp != nullptr; pp = pp->next)
    {
        pp->obj->printBST("");
        std::cout << std::endl;
    }
    return;
}

#endif
