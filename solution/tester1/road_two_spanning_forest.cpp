#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

const int MAXN = 1000;
const int MAXM = 500000;

struct Edge 
{
    int a, b, l;
    bool operator<(const Edge &e) const 
    {
        return l < e.l;
    }
} edge[MAXM + 5];

struct Disjoint_set 
{
    int n, djs_father[MAXN + 5];
    Disjoint_set(int _n = 0): n(_n) 
    {
        iota(djs_father + 1, djs_father + n + 1, 1);
    }
    int djs_find_root(int x) 
    {
        if (x == djs_father[x]) return x;
        return djs_father[x] = djs_find_root(djs_father[x]);
    }
    bool djs_union(int a, int b)
    {
        a = djs_find_root(a), b = djs_find_root(b);
        if (a == b) return false;
        djs_father[a] = b;
        return true;
    }
} spanning_forest[2];

vector<int> G[MAXN + 5], stk, bcc_id;
int low[MAXN + 5], dfn[MAXN + 5], dft, bcc_cnt;

void dfs(int u, int f) 
{
    dft++;
    dfn[u] = low[u] = dft;
    stk.push_back(u);
    for (int i : G[u])
    {
        if (!dfn[i]) 
        {
            dfs(i, u);
            low[u] = min(low[u], low[i]);
        }
        else if (i != f && dfn[u] > dfn[i])
        {
            low[u] = min(low[u], dfn[i]);
        }
    }
    if (low[u] == dfn[u]) 
    {
        bcc_cnt++;
        int tmp = 0;
        do 
        {
            tmp = stk.back();
            stk.pop_back();
            bcc_id[tmp] = bcc_cnt;
        } while (tmp != u);
    }
}

void build_bcc(int n) 
{
    bcc_id = vector<int>(n + 1);
    dft = bcc_cnt = 0;
    fill(dfn + 1, dfn + n + 1, 0);
    for (int i = 1; i <= n; i++)
    {
        if (!dfn[i])
        {
            dfs(i, i);
        }
    }
}

int main() 
{
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; i++) 
    {
        cin >> edge[i].a >> edge[i].b >> edge[i].l;
    }
    sort(edge + 1, edge + m + 1);
    vector<vector<int>> history;
    vector<int> length;
    for (int i = 0; i < 2; i++)
    {
        spanning_forest[i] = Disjoint_set(n);
    }
    for (int i = 1; i <= m; i++) 
    {
        int succ = 0;
        for (int j = 0; j < 2; j++)
        {
            if (!succ)
            {
                succ = spanning_forest[j].djs_union(edge[i].a, edge[i].b);
            }
        }
        if (succ) 
        {
            G[edge[i].a].push_back(edge[i].b);
            G[edge[i].b].push_back(edge[i].a);
            build_bcc(n);
            history.push_back(bcc_id);
            length.push_back(edge[i].l);
        }
    }
    int q;
    cin >> q;
    while (q--) 
    {
        int u, v;
        cin >> u >> v;
        int l = 0, r = history.size();
        while (l < r) 
        {
            int mid = (l + r) >> 1;
            if (history[mid][u] != history[mid][v])
            {
                l = mid + 1;
            }
            else
            {
                r = mid;
            }
        }
        if (l == int(history.size())) 
        { 
            cout << "-1\n";
        }
        else
        {
            cout << length[l] << "\n";
        }
    }
}
