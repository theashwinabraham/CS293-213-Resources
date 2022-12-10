/*
 * AUTHOR: ASHWIN ABRAHAM
 */

#include <bits/stdc++.h>
using namespace std;

struct Node {
    vector<int> neighbours;
};

void DFS(const vector<Node> &nodes)
{
    vector<bool> visited(nodes.size(), false);
    // for(int i = 0; i<nodes.size(); ++i) visited[i] = false;
    stack<pair<int, int>> s;
    s.push(pair<int, int>(0, 0));
    while(!s.empty())
    {
        pair<int, int> &p = s.top();
        if(!visited[p.first])
        {
            cout << "VISITING " << p.first << '\n';
            visited[p.first] = true;
        }
        bool remove = true;
        for(int i = p.second; i < nodes[p.first].neighbours.size(); ++i)
        {
            if(!visited[nodes[p.first].neighbours[i]])
            {
                p.second = i+1;
                s.push(pair<int, int>(nodes[p.first].neighbours[i], 0));
                remove = false;
                break;
            }
        }
        if(remove) s.pop();
    }
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
    DFS(nodes);
}