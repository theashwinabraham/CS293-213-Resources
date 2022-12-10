/*
 * AUTHOR: ASHWIN ABRAHAM
 */

#include <bits/stdc++.h>
using namespace std;

struct Node {
    vector<int> out_edges;
    vector<int> in_edges;
};

bool cyclic(const vector<Node> &nodes, int start = 0, int prev = -1)
{
    static int time = -1;
    static vector<int> arr(nodes.size(), -1);
    static vector<int> dep(nodes.size(), -1);
    static bool end_it_all = false;
    if(end_it_all) return true;

    ++time;
    arr[start] = time;

    for(int i = 0; i < nodes[start].out_edges.size(); ++i)
    {
        if(arr[nodes[start].out_edges[i]] == -1)
        {
            cyclic(nodes, nodes[start].out_edges[i], start);
        }
        else if(dep[nodes[start].out_edges[i]] == -1)
        {
            end_it_all = true;
            return true;
        }
    }

    ++time;
    dep[start] = time;

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
        nodes[n1].out_edges.push_back(n2);
        nodes[n2].in_edges.push_back(n1);
    }
    if(cyclic(nodes)) cout << "CYCLIC GRAPH\n";
    else cout << "ACYCLIC GRAPH\n";
}