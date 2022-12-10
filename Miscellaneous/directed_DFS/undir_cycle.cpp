/*
 * AUTHOR: ASHWIN ABRAHAM
 */

#include <bits/stdc++.h>
using namespace std;

struct Node {
    vector<int> neighbours;
};

bool cyclic(const vector<Node> &nodes, int start = 0, int prev = -1)
{
    static vector<bool> visited(nodes.size(), false);
    static bool end_it_all = false;
    if(end_it_all) return true;

    visited[start] = true;

    for(int i = 0; i<nodes[start].neighbours.size(); ++i)
    {
        if(!visited[nodes[start].neighbours[i]]) cyclic(nodes, nodes[start].neighbours[i], start);
        else if(prev != -1 && nodes[start].neighbours[i] != prev)
        {
            end_it_all = true;
            return true;
        }
    }
    return end_it_all;
}

int main()
{
    int N;
    cin >> N;
    vector<Node> nodes(N);
    int n1, n2;
    while(cin >> n1 >> n2)
    {
        nodes[n1].neighbours.push_back(n2);
        nodes[n2].neighbours.push_back(n1);
    }
    if(cyclic(nodes)) cout << "CYCLIC GRAPH\n";
    else cout << "ACYCLIC GRAPH\n";
}