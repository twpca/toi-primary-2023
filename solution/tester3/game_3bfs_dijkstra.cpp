// O(n + m log m)
// Dijkstra pick longest path 3 times
// Expect: WA
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

    void dijk(int cur) {
        priority_queue<P> q;
        fill(dis.begin(), dis.end(), INFMIN);
        fill(vis.begin(), vis.end(), false);

        LL d;
        q.emplace(w[cur], cur);
        while (!q.empty()) {
            tie(d, cur) = q.top();
            q.pop();
            if (vis[cur]) continue;
            vis[cur] = true;
            dis[cur] = d;
            for (int i: e[cur]) if (!vis[i]) {
                q.emplace(d+w[i], i);
            }
        }
    }
public:
    LL farest() {
        dis = vector<LL>(n+1);
        vis = vector<bool>(n+1);

        int res = 1;
        REP(repeat, 1, 3) {
            dijk(res);
            res = max_element(dis.begin() + 1, dis.begin() + n + 1) - dis.begin();
        }
        return dis[res];
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
