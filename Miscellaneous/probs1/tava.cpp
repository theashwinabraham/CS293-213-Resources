/*
 * AUTHOR: ASHWIN ABRAHAM
 */

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <chrono>

class Tava {
    private:
        std::vector<int> dosas;

    public:
        Tava(unsigned int num): dosas(num)
        {
            for(int i = 0; i < num; ++i)
            {
                dosas[i] = rand()%100;
                //std::cout << dosas[i] << '\n';
            }
        }

        unsigned int size()
        {
            return dosas.size();
        }

        void flip(int i)
        {
            std::reverse(dosas.end()-i, dosas.end());
        }

        void serve()
        {
            //std::cout << *(dosas.end()-1) << '\n';
            dosas.pop_back();
        }

        void selection_sort_serve()
        {
            while(size() > 0)
            {
                int smallest = dosas.size() - 1;
                for(int i = smallest - 1; i >= 0; --i)
                {
                    if(dosas[smallest] > dosas[i]) smallest = i;
                }

                flip(dosas.size() - smallest);
                serve();
            }
        }
};

int main()
{
    //std::cout << "Order of Dosas on Tava originally (bottom to top):\n";
    Tava t(100000);
    //std::cout << "Sort and Serve:\n";
    auto m = std::chrono::steady_clock::now();
    t.selection_sort_serve();
    auto dur = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - m);
    std::cout << dur.count() << '\n';
}