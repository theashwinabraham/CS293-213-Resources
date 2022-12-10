/*
 * AUTHOR: ASHWIN ABRAHAM
 */

#include <bits/stdc++.h>
using namespace std;

struct Node {
    vector<int> neighbours;
};

int DFS(const vector<Node> &nodes, int start = 0, int prev_node = -1)
{
    static vector<int> level(nodes.size(), -1);
    static bool end_it_all = false;
    if(end_it_all) return 0;
    if(prev_node == -1) level[start] = 0;
    else level[start] = 1 + level[prev_node];
    int min_b_level = INT32_MAX;
    for(int i = 0; i<nodes[start].neighbours.size(); ++i)
    {
        if(level[nodes[start].neighbours[i]] == -1)
        {
            int x = DFS(nodes, nodes[start].neighbours[i], start);
            if(min_b_level > x)
            {
                min_b_level = x;
            }
        }
        else if(nodes[start].neighbours[i] != prev_node)
        {
            if(min_b_level > level[nodes[start].neighbours[i]]) min_b_level = level[nodes[start].neighbours[i]];
        }
    }
    if(prev_node != -1 && min_b_level >= level[start])
    {
        end_it_all = true;
        return 0;
    }
    else if(prev_node == -1 && !end_it_all)
    {
        return 1;
    }
    return min_b_level;
}

int main()
{
    int N;
    cin >> N;
    vector<Node> nodes(N);
    int E;
    cin >> E;
    for(int i = 0; i<E; ++i)
    {
        int x, y;
        cin >> x >> y;
        nodes[x].neighbours.push_back(y);
        nodes[y].neighbours.push_back(x);
    }
    if(DFS(nodes)) cout << "2 edge connected\n";
    else cout << "Not 2 edge connected\n";
}