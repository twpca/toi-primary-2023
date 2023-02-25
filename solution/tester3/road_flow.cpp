// Fast O(log W * n^2m)
// subtask 1 & 2??
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
using namespace std;
using LL = long long;
using P = pair<int,int>;
constexpr int INF = 1'000'000'005;

class Graph {
protected:
    using T = tuple<int,int,int>;
    int n, m;
    vector<vector<P>> e;
    vector<T> edges;
};

class MaxflowSolver: public Graph {
    struct Edge {
        int u, v, r, opp;
        Edge () {}
        Edge (int _u, int _v, int _r, int _opp): u(_u), v(_v), r(_r), opp(_opp) {}
    };
    static constexpr int FLOW_INF = 1'000'000'000;
    int st, ed;
    vector<int> gap, dis;
    vector<vector<Edge>::iterator> arc;
    vector<vector<Edge>> flow_edge;

    Edge& rev_edge(const Edge& x) {
        return flow_edge[x.v][x.opp];
    }

    void add_edge(int u, int v, int w) {
        flow_edge[u].emplace_back(u, v, w, (int)flow_edge[v].size());
        flow_edge[v].emplace_back(v, u, w, (int)flow_edge[u].size() - 1);
    }

    bool bfs() {
        int cur;
        queue<int> q;
        fill(dis.begin(), dis.end(), 0);
        fill(gap.begin(), gap.end(), 0);

        dis[ed] = 1;
        gap[1] = 1;
        q.push(ed);
        while (!q.empty()) {
            cur = q.front();
            q.pop();
            for (auto i: flow_edge[cur]) if (rev_edge(i).r && !dis[i.v]) {
                dis[i.v] = dis[cur] + 1;
                gap[dis[i.v]]++;
                q.push(i.v);
            }
        }
        return dis[st];
    }

    int dfs(int cur, int flow) {
	    if (cur == ed) return flow;
	    int res = 0;
        for (auto it = arc[cur]; it != flow_edge[cur].end(); it++) {
            arc[cur] = it;
            if (dis[it->v] == dis[cur] - 1 && it->r) {
                int tmp = dfs(it->v, min(it->r, flow));
                res += tmp;
                flow -= tmp;
                it->r -= tmp;
                rev_edge(*it).r += tmp;
                if (!flow) return res;
            }
        }

	    if (dis[cur] >= 0) {
            gap[dis[cur]]--;
	        if (!gap[dis[cur]]) dis[st] = -1000;
            dis[cur] = -1000;
        }
	    return res;
    }

    bool check(int _st, int _ed, int w) {
        REP(i, 0, n) flow_edge[i].clear();
        for (auto i: edges) if (get<2>(i) <= w) {
            add_edge(get<0>(i), get<1>(i), 1);
        }
        st = _st;
        ed = _ed;

        int flow = 0;
        while (bfs()) {
            REP(i, 0, n) arc[i] = flow_edge[i].begin();
            flow += dfs(st, FLOW_INF);
            if (flow >= 2) break;
        }
        return flow >= 2;
    }

public:
    bool read() {
        int res = scanf("%d %d", &n, &m);
        if (res == -1) {
            return false;
        }

        e = vector<vector<P>> (n + 1);
        edges.clear();
        REP(i,1,m) {
            int x, y, z;
            scanf("%d %d %d", &x, &y, &z);
            e[x].emplace_back(y, z);
            e[y].emplace_back(x, z);
            edges.emplace_back(x, y, z);
        }

        gap = vector<int> (n + 1, 0);
        dis = vector<int> (n + 1, 0);
        arc = vector<vector<Edge>::iterator> (n + 1);
        flow_edge = vector<vector<Edge>> (n + 1);
        return true;
    }

    int ask(int x, int y) {
        int ok = INF;
        int ng = -1;
        int mid;
        while (abs(ok - ng) > 1) {
            mid = (ok + ng) / 2;
            if (check(x, y, mid)) ok = mid;
            else ng = mid;
        }
        return ok != INF ? ok : -1;
    }
};

MaxflowSolver flow;

int main()
{
    int q, x, y;
    while (flow.read()) {
        scanf("%d", &q);
        while (q--) {
            scanf("%d %d", &x, &y);
            printf("%d\n", flow.ask(x, y));
        }
    }
    return 0;
}
