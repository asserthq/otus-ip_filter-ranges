#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <range/v3/algorithm.hpp>
#include <range/v3/view.hpp>
#include <range/v3/iterator.hpp>

using IpType = std::vector<std::string>;

using IpPoolType = std::vector<IpType>;

template<std::size_t startIndex, std::size_t endIndex>
auto ipLexPartialGreaterComp(const IpType& lhs, const IpType& rhs) 
{
    return ranges::lexicographical_compare(
        lhs | ranges::views::drop(startIndex) | ranges::views::take(endIndex - startIndex),
        rhs | ranges::views::drop(startIndex) | ranges::views::take(endIndex - startIndex),
        [](auto&& lhs, auto&& rhs) {
            return ranges::greater{}(std::stoi(lhs), std::stoi(rhs));
        });
}

auto ipLexGreaterComp = ipLexPartialGreaterComp<0, 4>;

auto print(const IpPoolType& ip_pool, std::ostream& os = std::cout)
{
    for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
    {
        for (auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
        {
            if (ip_part != ip->cbegin())
            {
                os << ".";
            }
            os << *ip_part;
        }
        os << std::endl;
    }
}

auto filter(const IpPoolType& ip_pool, int first_part)
{
    auto val = IpType{ std::to_string(first_part) };

    auto startIt = ranges::lower_bound(ip_pool, val, ipLexPartialGreaterComp<0, 1>);

    auto endIt = ranges::upper_bound(ip_pool, val, ipLexPartialGreaterComp<0, 1>);

    return IpPoolType(startIt, endIt);
}

auto filter(const IpPoolType& ip_pool, int first_part, int second_part)
{
    auto val = IpType{ std::to_string(first_part), std::to_string(second_part) };

    auto startIt = ranges::lower_bound(ip_pool, val, ipLexPartialGreaterComp<0, 2>);

    auto endIt = ranges::upper_bound(ip_pool, val, ipLexPartialGreaterComp<0, 2>);
    
    return IpPoolType(startIt, endIt);
}

auto filter_any(const IpPoolType& ip_pool, int any_part)
{   
    auto r = IpPoolType{};

    auto val = std::to_string(any_part);

    ranges::copy_if(ip_pool, ranges::back_inserter(r), [val](auto&& ip) {
        return ranges::any_of(ip, [val](auto&& part) {
            return part == val;
        });
    });

    return r;
}
