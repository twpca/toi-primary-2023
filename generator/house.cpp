#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <random>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_set>
#include <vector>

using i32 = std::int32_t;
using u32 = std::uint32_t;
using i64 = std::int64_t;
using u64 = std::uint64_t;

constexpr i32 MAX_X = 1'000'000'000;
constexpr i32 MIN_X = -MAX_X;

class arg_error : std::runtime_error
{
public:
    arg_error() : std::runtime_error("arg_error: type n subtask_index seed") {}
};

struct point_t
{
    i32 x;
    i32 y;
    bool operator==(const point_t &o) const { return x == o.x && y == o.y; }
};

void GenerateRandom(size_t n, std::mt19937 &rng, std::ostream &os)
{
    const size_t m = std::uniform_int_distribution<size_t>(990, 1000)(rng);
    std::uniform_int_distribution<i32> x_dist(MIN_X, MAX_X);
    std::uniform_int_distribution<i32> r_dist(0, MAX_X);

    auto my_hash = [](const point_t &p)
    { return 1'000'000'007ll * (1ll * p.x - MIN_X) + (1ll * p.y - MIN_X); };
    std::vector<point_t> v(n + m);
    {
        std::unordered_set<point_t, decltype(my_hash)> h(1, my_hash);
        for (auto &x : v)
        {
            for (size_t t = 1 << 30; t;)
            {
                x.x = x_dist(rng);
                x.y = x_dist(rng);
                auto it = h.insert(x);
                if (it.second)
                    break;
                if (--t == 0)
                {
                    throw std::runtime_error("cursed");
                }
            }
        }
    }
    os << n << " " << m << '\n';
    for (size_t i = 0; i < n; ++i)
    {
        auto &x = v[i];
        os << x.x << " " << x.y << " " << r_dist(rng) << '\n';
    }
    for (size_t i = 0; i < m; ++i)
    {
        auto &x = v[i + n];
        os << x.x << " " << x.y << '\n';
    }
    os.flush();
}

int main(int argc, char **argv)
{
    auto arg_it = argv + 1;
    auto arg_ed = argv + argc;
    if (!(arg_it < arg_ed))
        throw arg_error();
    const std::string_view type = *(arg_it++);
    if (!(arg_it < arg_ed))
        throw arg_error();
    const i32 n = std::stoi(*(arg_it++));
    if (!(arg_it < arg_ed))
        throw arg_error();
    const size_t subtask_index = std::stoul(*(arg_it++));
    if (!(arg_it < arg_ed))
        throw arg_error();
    const size_t seed = std::stoul(*(arg_it++), nullptr, 0);
    if (!(arg_it < arg_ed))
        throw arg_error();
    const size_t serial_number = std::stoul(*(arg_it++));
    if (arg_it < arg_ed)
        throw arg_error();
    if (subtask_index >= 4 || subtask_index <= 0)
    {
        std::ostringstream os;
        os << "subtask_index = " << subtask_index << " must in [1,2,3]";
        throw std::runtime_error(os.str());
    }
    std::mt19937 rng(seed);
    if (type == "random")
    {
        std::ostringstream oss;
        oss << "./" << subtask_index;
        oss << "_" << std::setfill('0') << std::setw(4) << serial_number;
        oss << "_" << type;
        oss << "_" << std::setfill('0') << std::hex << std::setw(8) << seed;
        oss << ".in";
        std::ofstream fp(oss.str());
        GenerateRandom(n, rng, fp);
    }
    else
    {
        std::ostringstream oss;
        oss << "unknown type: " << type;
        throw std::runtime_error(oss.str());
    }
}
