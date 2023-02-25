#pragma GCC optimize("O3")
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <vector>
#include <utility>
#include <tuple>
using i32 = std::int32_t;
using u32 = std::uint32_t;
using i64 = std::int64_t;
using u64 = std::uint64_t;
struct house_t
{
    i64 x;
    i64 y;
    i64 d;
    i32 r;
    i32 index;
};
struct station_t
{
    i64 x;
    i64 y;
};
bool solve()
{
    size_t n{};
    size_t m{};
    if (!(std::cin >> n >> m))
        return false;
    std::vector<house_t> h(n);
    {
        i32 index = 0;
        for (auto &x : h)
        {
            std::cin >> x.x >> x.y >> x.r;
            x.index = ++index;
            x.d = 0x7fff'ffff'ffff'ffffll;
        }
    }
    {
        std::vector<station_t> s(m);
        for (auto &x : s)
        {
            std::cin >> x.x >> x.y;
        }
        for (auto &x : h)
        {
            for (auto &y : s)
            {
                auto dx = x.x - y.x;
                auto dy = x.y - y.y;
                x.d = std::min(x.d, dx * dx + dy * dy);
            }
        }
    }
    std::sort(
        h.begin(), h.end(),
        [](const house_t &l, const house_t &r)
        { return std::tie(l.d, l.r, l.index) < std::tie(r.d, r.r, r.index); });
    for (auto &x : h)
    {
        std::cout << x.index << '\n';
    }
    std::cout.flush();
    return true;
}

void init_io()
{
    std::cin.tie(nullptr);
    std::ios::sync_with_stdio(false);
}

int main()
{
    init_io();
    for (; solve();)
        ;
}
