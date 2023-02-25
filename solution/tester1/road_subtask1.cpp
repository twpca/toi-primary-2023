#include <iostream>
#include <vector>
#include <algorithm>
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

vector<int> G[MAXN + 5];
int vis[MAXN + 5];

void dfs(int u) 
{
    vis[u] = 1;
    for (int i : G[u])
    {
        if (!vis[i])
        {
            dfs(i);
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
    int q;
    cin >> q;
    while (q--) 
    {
        int u, v;
        cin >> u >> v;
        int flag = 1;
        for (int j = 1; j <= m; j++) 
        {
            for (int k = 1; k <= n; k++)
            {
                G[k].clear();
                vis[k] = 0;
            }
            for (int k = 1; k <= m; k++)
            {
                if (j != k) 
                {
                    G[edge[k].a].push_back(edge[k].b);
                    G[edge[k].b].push_back(edge[k].a);
                }
            }
            dfs(u);
            if (!vis[v]) 
            { 
                flag = 0;
            }
        }
        if (flag) 
        { 
            cout << "1\n";
        }
        else
        { 
            cout << "-1\n";
        }
    }
}
