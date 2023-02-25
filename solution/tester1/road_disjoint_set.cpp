#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 1005;
const int MAXM = 500005;

struct Edge 
{
    int a, b, l;
    bool operator<(const Edge &e) const 
    {
        return l < e.l;
    }
} edge[MAXM];

vector<int> G[MAXN];
bool used[MAXM];
int djs_father[MAXN], sz[MAXN], light[MAXN], up[MAXN];
int father[MAXN], deep[MAXN];

int djs_find_root(int x) 
{
    while (x != djs_father[x]) 
    {
        x = djs_father[x];
    }
    return x;
}

bool djs_union(int a, int b, int l) 
{
    a = djs_find_root(a), b = djs_find_root(b);
    if (a == b)
    {
        return false;
    }
    if (sz[a] < sz[b]) 
    {
        swap(a, b);
    }
    djs_father[b] = a;
    up[b] = l;
    sz[a] += sz[b];
    if (deep[light[a]] > deep[light[b]])
        light[a] = light[b];
    return true;
}

void dfs(int u, int f, int d) 
{
    father[u] = f, deep[u] = d;
    for (int i : G[u])
    {
        if (i != f)
        {
            dfs(i, u, d + 1);
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
    iota(djs_father + 1, djs_father + n + 1, 1);
    fill(sz + 1, sz + n + 1, 1);
    for (int i = 1; i <= m; i++) 
    {
        used[i] = djs_union(edge[i].a, edge[i].b, edge[i].l);
        if (used[i]) 
        {
            G[edge[i].a].push_back(edge[i].b);
            G[edge[i].b].push_back(edge[i].a);
        }
    }
    dfs(1, 1, 0);
    iota(djs_father + 1, djs_father + n + 1, 1);
    iota(light + 1, light + n + 1, 1);
    fill(sz + 1, sz + n + 1, 1);
    for (int i = 1; i <= m; i++)
    {
        if (!used[i]) 
        {
            int a = djs_find_root(edge[i].a);
            int b = djs_find_root(edge[i].b);
            while (a != b) 
            {
                if (deep[light[a]] > deep[light[b]])
                {
                    swap(a, b);
                }
                djs_union(b, father[light[b]], edge[i].l);
                a = djs_find_root(a), b = djs_find_root(b);
            }
        }
    }
    int q;
    cin >> q;
    while (q--) 
    {
        int u, v, ans = 0;
        cin >> u >> v;
        if (djs_find_root(u) != djs_find_root(v))
        { 
            cout << "-1\n";
        }
        else 
        {
            while (u != v) 
            {
                if (sz[u] < sz[v]) 
                {
                    swap(u, v);
                }
                ans = max(ans, up[v]);
                v = djs_father[v];
            }
            cout << ans << "\n";
        }
    }
}
