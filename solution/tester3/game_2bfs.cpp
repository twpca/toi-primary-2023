// O(n + m)
// Greedily pick a longest path using bfs on tree + cyclic DP
// Expect: w_i >= 0 subtasks AC
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M 100005
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

class GreedySolver: public Jellyfish {
    using P = pair<LL, int>;
    vector<LL> dis;
    vector<bool> vis;

    void bfs(int cur) {
        queue<int> q;
        fill(dis.begin(), dis.end(), INFMIN);
        fill(vis.begin(), vis.end(), false);

        q.emplace(cur);
        dis[cur] = w[cur];
        vis[cur] = true;
        while (!q.empty()) {
            cur = q.front();
            q.pop();

            for (int i: e[cur]) if (!vis[i]) {
                q.emplace(i);
                dis[i] = dis[cur] + w[i];
                vis[i] = true;
            }
        }
    }

    LL max_down_path(int cur, int fa, LL s) { // max path started from cycle root
        LL res = s;
        for (int i: e[cur]) if (!is_root[i] && i!=fa) {
            res = max(res, max_down_path(i, cur, s + w[i]));
        }
        return res;
    }
public:
    LL farest() {
        // tree farest
        int c0 = -1, c1 = -1;
        if ((int)cycle.size() > 1) {
            c0 = cycle[0];
            c1 = cycle.back();
            remove_edge(c0, c1);
        }
        dis = vector<LL>(n+1);
        vis = vector<bool>(n+1);

        int tmp = 1;
        REP(repeat, 1, 2) {
            bfs(tmp);
            tmp = max_element(dis.begin() + 1, dis.begin() + n + 1) - dis.begin();
        }
        LL res = dis[tmp];

        // max path through c0, c1
        if (c0 != -1) {
            int cs = (int) cycle.size();
            vector<LL> dpl(cs), dpr(cs), wsum(cs);

            // init
            REP(i, 0, cs-1) {
                int root = cycle[i];
                wsum[i] = w[root];
                dpl[i] = dpr[i] = max_down_path(root, -1, w[root]);
                if (i > 0) {
                    wsum[i] += wsum[i-1];
                }
            }

            // dpl, dpr
            REP(i, 0, cs-1) {
                if (i > 0) {
                    dpl[i] += wsum[i-1];
                }
            }

            for (int i=cs-1; i>=0; i--) {
                if (i < cs-1) {
                    dpr[i] += wsum[cs-1] - wsum[i];
                    dpr[i] = max(dpr[i], dpr[i+1]);
                }
            }

            // update
            REP(i, 0, cs-1) {
                LL d = dpl[i];
                if (i != cs-1) {
                    d += dpr[i+1];
                }
                res = max(res, d);
            }
        }
        return res;
    }
};
GreedySolver jellyfish;

int main()
{
    while (jellyfish.read()) {
        printf("%lld\n", jellyfish.farest());
    }
    return 0;
}
