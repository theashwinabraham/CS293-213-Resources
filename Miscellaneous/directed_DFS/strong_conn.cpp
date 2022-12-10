/*
 * AUTHOR: ASHWIN ABRAHAM
 */

#include <bits/stdc++.h>
using namespace std;

struct Node {
    vector<int> out_edges;
    vector<int> in_edges;
};

int str_conn(const vector<Node> &nodes, int start = 0, int prev = -1)
{
    static int time = -1;
    static vector<int> arr(nodes.size(), -1);
    static vector<int> dep(nodes.size(), -1);
    static bool end_it_all = false;
    if(end_it_all) return 0;

    ++time;
    arr[start] = time;

    int min_arr_time = INT32_MAX;
    for(int i = 0; i<nodes[start].out_edges.size(); ++i)
    {
        
        if(arr[nodes[start].out_edges[i]] == -1)
        {
            int x = str_conn(nodes, nodes[start].out_edges[i], start);
            if(min_arr_time > x) min_arr_time = x;
        }
        else
        {
            if(arr[nodes[start].out_edges[i]] < arr[start] && min_arr_time > arr[nodes[start].out_edges[i]]) min_arr_time = arr[nodes[start].out_edges[i]];
        }
    }

    ++time;
    dep[start] = time;
    if(prev != -1 && min_arr_time >= arr[start])
    {
        end_it_all = true;
        return 0;
    }
    if(prev == -1) return !end_it_all;
    return min_arr_time;
}

int main()
{
    int N;
    cin >> N;
    vector<Node> nodes(N);
    int x, y;
    while(cin >> x >> y)
    {
        nodes[x].out_edges.push_back(y);
        nodes[y].in_edges.push_back(x);
    }
    if(str_conn(nodes)) cout << "STRONGLY CONNECTED\n";
    else cout << "NOT STRONGLY CONNECTED\n";
}