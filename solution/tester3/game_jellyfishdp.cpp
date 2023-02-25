// O(n + m)
// Expect: AC
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
using namespace std;
using LL = long long;
constexpr LL INFMIN = -(1LL << 60);

class Jellyfish {
protected:
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

public:
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

class DPSolver: public Jellyfish {
    vector<LL> dp, down;

    void dfs(int cur, int fa) {
        down[cur] = w[cur];
        dp[cur] = w[cur];
        for (int i: e[cur]) if (!is_root[i] && i != fa) {
            dfs(i, cur);
            down[cur] = max(down[cur], w[cur] + down[i]);
            dp[cur] = max(dp[cur], dp[i]);
        }

        LL mx1 = 0LL; // can be empty
        LL mx2 = 0LL;
        for (int i: e[cur]) if (!is_root[i] && i != fa) {
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
    LL farest() {
        dp = vector<LL> (n+1);
        down = vector<LL> (n+1);
        LL res = INFMIN;
        for (int i: cycle) if (is_root[i]) {
            dfs(i, -1);
            res = max(res, dp[i]);
        }

        int cs = (int)cycle.size();
        if (cs > 1) {
            vector<LL> lcost(cs*2), rcost(cs*2), wsum(cs*2);
            REP(i, 0, 2*cs-1) {
                int root = cycle[i % cs];
                wsum[i] = w[root];
                rcost[i] = down[root];
                if (i > 0) {
                    wsum[i] += wsum[i-1];
                    rcost[i] += wsum[i-1];
                }
                lcost[i] = down[root] - wsum[i];
            }

            int fr=0, bk=0;
            vector<int> deq(cs*2);
            REP(i, 0, 2*cs-1) {
                while (bk > fr && i - deq[fr] >= cs) fr++;
                if (bk > fr) {
                    res = max(res, rcost[i] + lcost[deq[fr]]);
                }
                while (bk > fr && lcost[i] >= lcost[deq[bk-1]]) bk--;
                deq[bk++] = i;
            }
        }
        return res;
    }
};
DPSolver jellyfish;

int main()
{
    while (jellyfish.read()) {
        printf("%lld\n", jellyfish.farest());
    }
    return 0;
}
