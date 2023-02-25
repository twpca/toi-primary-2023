#include "testlib.h"
#include <algorithm>
#include <set>
#include <utility>
#include <string>
#include <cassert>
#include <numeric>

constexpr int SUBTASKS = 4;
constexpr int MN_N = 2;
constexpr int MX_N[SUBTASKS + 1] = {1000, 100, 500, 1000, 1000};
constexpr int MX_M[SUBTASKS + 1] = {500'000, 300, 1000, 3000, 500'000};
constexpr int MN_Q = 1;
constexpr int MX_Q[SUBTASKS + 1] = {500'000, 300, 1000, 500'000, 500'000};

constexpr int MN_C = 1;
constexpr int MX_C[SUBTASKS + 1] = {1'000'000'000, 1, 1'000'000'000, 1'000'000'000, 1'000'000'000};

int subtask(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        if (!strcmp("--testcase", argv[i - 1])) {
            int subtask = atoi(argv[i]);
            assert(0 <= subtask && subtask <= SUBTASKS);
            return subtask;
        }
    }
    assert(0);
    return -1;
}

struct Disjoint_set {
    int n, boss[MX_N[SUBTASKS] + 5];
    Disjoint_set(int _n = 0): n(_n) {
        std::iota(boss + 1, boss + n + 1, 1);
    }
    int finds(int x) {
        if (x == boss[x]) return x;
        return boss[x] = finds(boss[x]);
    }
    bool Union(int a, int b) {
        a = finds(a), b = finds(b);
        if (a == b) return false;
        boss[a] = b;
        return true;
    }
} djs;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int s = subtask(argc, argv);
    int n = inf.readInt(MN_N, MX_N[s], "n"); inf.readSpace();
    int m = inf.readInt(n - 1, std::min(MX_M[s], n * (n - 1) / 2), "m"); inf.readChar('\n');
    int conn = n;

    std::set<std::pair<int, int>> vis;
    djs = Disjoint_set(n);

    auto add_edge = [&](int a, int b) {
        if (a > b) std::swap(a, b);
        ensuref(a != b, "loop");
        ensuref(vis.insert(std::make_pair(a, b)).second, "multiple edges");
        conn -= djs.Union(a, b);
    };

    for (int i = 1; i <= m; ++i) {
        int a = inf.readInt(1, n, "a_" + std::to_string(i)); inf.readSpace();
        int b = inf.readInt(1, n, "b_" + std::to_string(i)); inf.readSpace();
        int l = inf.readInt(MN_C, MX_C[s], "l_" + std::to_string(i)); inf.readChar('\n');
        add_edge(a, b);
    }

    ensuref(conn == 1, "not connected");

    int q = inf.readInt(MN_Q, MX_Q[s], "q"); inf.readChar('\n');

    for (int i = 1; i <= q; ++i) {
        int u = inf.readInt(1, n, "u_" + std::to_string(i)); inf.readSpace();
        int v = inf.readInt(1, n, "v_" + std::to_string(i)); inf.readChar('\n');
        ensuref(u != v, "u == v");
    }

    inf.readEof();
    return 0;
}
