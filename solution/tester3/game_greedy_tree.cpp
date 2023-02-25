// O(n + m)
// Greedily remove an edge on cycle, output the max distance on tree
// Expect: WA
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M 100005
using namespace std;
using LL = long long;
using Unif = uniform_int_distribution<>;
constexpr LL INFMIN = -(1LL << 60);

class Jellyfish {
public:
    int n, m;
    vector<bool> is_root;
    vector<int> w, cycle;
    vector<vector<int>> e;

    int pop_cycle(int cur, int fa, vector<bool>& _vis, vector<bool>& _ins) {
        _vis[cur] = true;
        _ins[cur] = true;
        int res = 0;
        for (int i: e[cur]) if (i!=fa) {
            if (!_vis[i]) {
                int to = pop_cycle(i, cur, _vis, _ins);
                if (to) {
                    assert(!res);
                    res = to;
                }
            } else if (_vis[i] && _ins[i]) {
                res = i;
            }
        }

        if (res) {
            cycle.emplace_back(cur);
            if (res == cur) res = 0;
        }
        _ins[cur] = false;
        return res;
    }

    void find_roots() {
        vector<bool> vis (n+1, false);
        vector<bool> ins (n+1, false);

        if (m == n-1) {
            cycle.push_back(1);
        } else {
            pop_cycle(1, -1, vis, ins);
            assert(cycle.size());
        }

        is_root = vector<bool> (n+1, false);
        for (int i: cycle) {
            is_root[i] = true;
        }
    }

    void remove_edge(int x, int y) { // O(n)
        e[x].erase(
            remove(e[x].begin(), e[x].end(), y),
            e[x].end()
        );
        e[y].erase(
            remove(e[y].begin(), e[y].end(), x),
            e[y].end()
        );
    }

    bool read() {
        int res = scanf("%d %d", &n, &m);
        if (res == -1) {
            return false;
        }

        cycle.clear();
        w = vector<int> (n+1);
        e = vector<vector<int>> (n+1);
        REP(i,1,m) {
            int x, y;
            scanf("%d %d", &x, &y);
            e[x].emplace_back(y);
            e[y].emplace_back(x);
        }
        REP(i,1,n) scanf("%d", &w[i]);
        find_roots();
        return true;
    }
};

class Tree {
    int n;
    vector<int> w;
    vector<vector<int>> e;

    vector<LL> dp, down;

    void dfs(int cur, int fa) {
        down[cur] = w[cur];
        dp[cur] = w[cur];
        for (int i: e[cur]) if (i != fa) {
            dfs(i, cur);
            down[cur] = max(down[cur], w[cur] + down[i]);
            dp[cur] = max(dp[cur], dp[i]);
        }

        LL mx1 = 0LL; // can be empty
        LL mx2 = 0LL;
        for (int i: e[cur]) if (i != fa) {
            if (down[i] > mx1) {
                mx2 = mx1;
                mx1 = down[i];
            } else if (down[i] > mx2) {
                mx2 = down[i];
            }
        }
        dp[cur] = max(dp[cur], mx1 + mx2 + w[cur]);
    }

public:
    void init(int _n, vector<int> _w) {
        n = _n;
        w = _w;
        e = vector<vector<int>> (n+1);
        dp = vector<LL> (n+1);
        down = vector<LL> (n+1);
    }

    void clear_edges() {
        e = vector<vector<int>> (n+1);
    }

    void add_edge(int x, int y) {
        e[x].emplace_back(y);
        e[y].emplace_back(x);
    }

    LL farest() {
        dfs(1, -1);
        return dp[1];
    }
};
Jellyfish jellyfish;
Tree tree;
mt19937_64 Rng;

pair<int,int> random_cycle_edge() {
    int sz = jellyfish.cycle.size();
    int x = Unif(0, sz-1)(Rng);
    int y = (x == sz-1) ? 0 : x + 1;

    x = jellyfish.cycle[x];
    y = jellyfish.cycle[y];
    return make_pair(x, y);
}

int main()
{
    Rng.seed(114514);
    while (jellyfish.read()) {
        tree.init(jellyfish.n, jellyfish.w);

        LL ans = INFMIN;
        REP(i,1,10) {
            int x, y;
            tie(x, y) = random_cycle_edge();
            tree.clear_edges();

            REP(j, 1, jellyfish.n) for (int k: jellyfish.e[j]) {
                if (j > k) continue;
                if (j==x && k==y) continue;
                if (j==y && k==x) continue;
                tree.add_edge(j, k);
            }
            ans = max(ans, tree.farest());
        }
        printf("%lld\n", ans);
    }
    return 0;
}
