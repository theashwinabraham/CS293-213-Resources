/*
 * AUTHOR: ASHWIN ABRAHAM
 */

#include <cstdlib>
#include <iterator>
#include <utility>
#include <iostream>
#include <vector>

template <typename T> // T should be an array iterator (operator*, operator+(int), operator++ should be defined), 
// and operator< should be defined on the result of operator*
// begin points to first element, end points to one past the second element
void quicksort(const T& begin, const T& end)
{
    if(!(begin < end)) return;
    T pivot = begin + rand() % std::distance(begin, end);
    int num_less = 0;
    for(T iter = begin; iter != end; iter++)
    {
        if(*iter < *pivot)
        {
            std::swap(*iter, *(begin + num_less));
            if(pivot == begin + num_less) pivot = iter;
            ++num_less;
        }
    }
    std::swap(*pivot, *(begin+num_less));
    quicksort(begin, begin + num_less);
    quicksort(begin + num_less + 1, end);
}

int main()
{
    std::vector<int> arr = {1};
    for(int i = 0; i<arr.size(); i++) std::cout << arr[i] << '\n';
    std::cout << '\n';
    quicksort(arr.begin(), arr.end());
    for(int i = 0; i<arr.size(); i++) std::cout << arr[i] << '\n';
}