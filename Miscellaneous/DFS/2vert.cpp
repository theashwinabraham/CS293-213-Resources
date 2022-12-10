/*
 * AUTHOR: ASHWIN ABRAHAM
 */

#include <bits/stdc++.h>
using namespace std;

struct Node {
    vector<int> neighbours;
};

int two_vert(const vector<Node> &nodes, int start = 0, int prev = -1)
{
    static vector<int> level(nodes.size(), -1);
    static bool end_it_all = false;
    if(end_it_all) return 0;
    if(prev == -1) level[start] = 0;
    else level[start] = level[prev] + 1;


    int min_inc = INT32_MAX;
    int min_exc = INT32_MAX;
    int num_children = 0;
    for(int i = 0; i < nodes[start].neighbours.size(); ++i)
    {
        if(level[nodes[start].neighbours[i]] == -1)
        {
            ++num_children;
            if(prev == -1 && num_children > 1)
            {
                end_it_all = true;
                return 0;
            }
            int x = two_vert(nodes, nodes[start].neighbours[i], start);
            if(min_exc > x) min_exc = x;
            if(min_inc > x) min_inc = x;
        }
        else if(nodes[start].neighbours[i] != prev)
        {
            if(min_inc > level[nodes[start].neighbours[i]]) min_inc = level[nodes[start].neighbours[i]];
        }
    }
    if(prev != -1 && num_children > 0 && min_exc >= level[start])
    {
        end_it_all = true;
        return 0;
    }
    else if(prev == -1 && !end_it_all)
    {
        return 1;
    }
    return min_inc;
}

int main()
{
    int N;
    cin >> N;
    vector<Node> nodes(N);
    int v1, v2;
    while(cin >> v1 >> v2)
    {
        nodes[v1].neighbours.push_back(v2);
        nodes[v2].neighbours.push_back(v1);
    }
    if(two_vert(nodes)) cout << "2 vertex connected\n";
    else cout << "not 2 vertex connected\n";
}