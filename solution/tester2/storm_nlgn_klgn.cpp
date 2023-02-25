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

struct ele_t
{
    i64 fixed;
    i64 a;
    i64 *ptr;
    i64 v;
    ele_t() = default;
    ele_t(i64 f, i64 a_, i64 *ptr_) : fixed(f), a(a_), ptr(ptr_), v()
    {
        update();
    }
    void update() { v = fixed + a * (*ptr); }
    void next()
    {
        ++ptr;
        update();
    }
    bool empty(i64 *ed) const { return ptr + 1 == ed; }
    bool operator<(const ele_t &o) const { return v > o.v; }
    void out(std::ostream &os) const
    {
        auto ans = -v;
        if (ans % 2)
            os << ans << '\n' << 2 << '\n';
        else
            os << ans / 2 << '\n' << 1 << '\n';
    }
};

bool solve()
{
    size_t n{};
    size_t k{};
    if (!(std::cin >> n >> k))
        return false;
    std::vector<i64> w(n);
    for (auto &x : w)
    {
        std::cin >> x;
        x *= -1;
    }
    std::sort(w.begin(), w.end());
    std::vector<ele_t> h(n);
    for (size_t i = 0; i + 1 < n; ++i)
    {
        h[i] = ele_t{w[i], 1, w.data() + i + 1};
    }
    h.back() = ele_t{0, 2, w.data()};
    std::make_heap(h.begin(), h.end());
    auto ed = w.data() + n;
    for (size_t i = 1; i < k; ++i)
    {
        std::pop_heap(h.begin(), h.end());
        auto &top = h.back();
        //top.out(std::cout);
        if (top.empty(ed))
        {
            h.pop_back();
            continue;
        }
        else
        {
            top.next();
            std::push_heap(h.begin(), h.end());
        }
    }
    h[0].out(std::cout);
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
