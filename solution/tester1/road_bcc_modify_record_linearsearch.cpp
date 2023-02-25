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
    bcc_id.resize(n + 1);
    iota(bcc_id.begin(), bcc_id.end(), 0);
    for (int i = 1; i <= m; i++) 
    {
        if (bcc_id[edge[i].a] != bcc_id[edge[i].b]) 
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
        if (history.back()[u] != history.back()[v]) 
        { 
            cout << "-1\n";
        }
        else 
        {
            for (int i = 0; i < int(history.size()); i++)
            {
                if (history[i][u] == history[i][v]) 
                {
                    cout << length[i] << "\n";
                    break;
                }
            }
        }
    }
}
