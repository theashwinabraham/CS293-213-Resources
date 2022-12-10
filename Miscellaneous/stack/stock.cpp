/*
 * AUTHOR: ASHWIN ABRAHAM
 */

#include <bits/stdc++.h>
using namespace std;

vector<int> arr_span(const vector<int>& prices)
{
    assert(prices.size() > 0);

    vector<int> ans;
    ans.push_back(-1);
    
    for(int i = 1; i < prices.size(); ++i)
    {
        if(prices[i] < prices[i-1]) ans.push_back(i-1);
        else
        {
            ans.push_back(ans[i-1]);
            while(ans[i] != -1 && prices[ans[i]] <= prices[i])
            {
                ans[i] = ans[ans[i]];
            }
        }
    }
    return ans;
}

vector<int> stack_span(const vector<int>& prices)
{
    assert(prices.size() > 0);

    vector<int> ans;
    ans.push_back(-1);

    stack<int> helper; // at any point in the loop, helper will not contain indices i that have p < i < q and prices[i] < min(prices[p], prices[q])
    helper.push(0);

    for(int i = 1; i < prices.size(); ++i)
    {
        if(prices[i] < prices[i-1]) ans.push_back(i-1);
        else
        {
            ans.push_back(helper.top());
            while(prices[i] >= prices[ans[i]] && !helper.empty())
            {
                helper.pop();
                ans[i] = helper.empty()? -1:helper.top();
            }
        }
        helper.push(i);
    }
    return ans;
}

int main()
{
    srand(time(NULL));
    vector<int> prices;
    int n;
    std::cin >> n;
    for(int i = 0; i<n; ++i)
    {
        int price;
        std::cin >> price;
        prices.push_back(price);
    }
    
    vector<int> v = stack_span(prices);
    for(int i = 0; i < v.size(); ++i) std::cout << i-v[i] << '\n';
}