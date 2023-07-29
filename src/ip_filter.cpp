#include <vector>
#include <range/v3/algorithm.hpp>
#include <gtest/gtest.h>

int main()
{
    std::vector<int> v{ 3, 1, 2 };
    ranges::sort(v);
    for(auto&& el : v)
    {
        std::cout << el << " ";
    }
    std::cout << std::endl;
    return 0;
}