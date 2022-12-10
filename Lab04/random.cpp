#include <iostream>
#include <cstdlib>

int main()
{
    std::cout << (void*) main << '\n';
    for(int i = 0; i<10; ++i) std::cout << rand()% 1000 << rand() % 1000 << '\n';
}