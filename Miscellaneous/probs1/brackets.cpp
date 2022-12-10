/*
 * AUTHOR: ASHWIN ABRAHAM
 */

#include <iostream>
#include <stack>

int main()
{
    char c;
    std::stack<char> s;
    while(std::cin >> c)
    {
        if(c == '(' || c == '[' || c == '{') s.push(c);
        else
        {
            if(c == ')')
            {
                if(s.top() == '(') s.pop();
                else
                {
                    std::cout << "\nInvalid\n";
                    return 0;
                }
            }
            else if(c == ']' || c == '}')
            {
                if(s.top() == c - 2) s.pop();
                else
                {
                    std::cout << "\nInvalid\n";
                    return 0;
                }
            }
        }
    }
    if(!s.empty())
    {
        std::cout << "\nInvalid\n";
        return 0;
    }
    std::cout << "\nValid\n";
    return 0;
}