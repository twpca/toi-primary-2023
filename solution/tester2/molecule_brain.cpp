#pragma GCC optimize("O3")
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <tuple>
#include <utility>
#include <vector>
using i32 = std::int32_t;
using u32 = std::uint32_t;
using i64 = std::int64_t;
using u64 = std::uint64_t;

bool solve()
{
    i32 a, b, c;
    if (!(std::cin >> a >> b >> c))
        return false;
    if (c % 2 != 0)
    {
        std::cout << "-1\n";
        return true;
    }
    const bool is_swap = a < b;
    if (is_swap)
        std::swap(a, b);
    const i32 cc = c / 2;
    i32 min_activity = 1 << 30;
    std::string ans{};
    if(c == 0 && b == 0)
    {
        min_activity = a;
        ans.append(a, 'X');
    }
    i32 brain_count = 10;
    for (i32 i = 0; i <= cc; ++i)
    {
        i32 p_yy = i;
        i32 p_x = b;
        i32 p_xx = cc - p_yy;
        i32 p_y = b + cc - 2 * p_yy;
        i32 r_a = a - p_y;
        if (!(a >= p_y && p_y >= 0 && p_x + 2 * p_xx <= a + cc))
            continue;
        if (r_a > 0 && p_xx == 0)
            continue;
        const i32 more = p_xx == 0 ? 0 : r_a / p_xx;
        i32 number_of_more_plus_one = p_xx == 0 ? 0 : r_a % p_xx;
        i32 activity = 0;
        std::string s{};
        for (; p_x + p_xx + p_y + p_yy;)
        {
            if (p_xx)
            {
                const i32 num = 2 + more + (number_of_more_plus_one > 0);
                activity = std::max(activity, num);
                s.append(num, 'X');
                --number_of_more_plus_one;
                --p_xx;
            }
            else if (p_x)
            {
                activity = std::max(activity, 1);
                s.append(1, 'X');
                --p_x;
            }
            else
            {
                throw std::runtime_error("X");
            }
            if (p_yy)
            {
                activity = std::max(activity, 2);
                s.append(2, 'Y');
                --p_yy;
            }
            else if (p_y)
            {
                activity = std::max(activity, 1);
                s.append(1, 'Y');
                --p_y;
            }
            else
            {
                throw std::runtime_error("Y");
            }
        }
        if (min_activity > activity)
        {
            min_activity = activity;
            ans = std::move(s);
        }
        if (--brain_count <= 0)
            break;
    }
    if (min_activity == (1 << 30))
    {
        std::cout << "-1\n";
    }
    else
    {
        std::cout << min_activity << '\n';
        if (is_swap)
        {
            for (auto &ch : ans)
                ch = ch == 'X' ? 'Y' : 'X';
        }
        std::cout << ans << '\n';
    }
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
        std::cout.flush();
}
