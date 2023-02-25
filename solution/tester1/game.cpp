#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
using namespace std;

const int MAXN = 100005;

int arr[MAXN], deg[MAXN];
long long len[MAXN][2], sum[2 * MAXN];
vector<int> G[MAXN];

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    if (m == n - 1)
    {
        G[1].push_back(1), G[1].push_back(1);
    }
    while (m--) 
    {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i], deg[i] = G[i].size();
    }
    if (*max_element(arr + 1, arr + n + 1) < 0)
    {
        cout << *max_element(arr + 1, arr + n + 1) << "\n";
        exit(0);
    }
    queue<int> q;
    for (int i = 1; i <= n; i++)
    {
        if (deg[i] == 1)
        {
            q.push(i);
        }
    }

    auto insert = [&](int u, long long l) 
    {
        if (l > len[u][0]) 
        {
            len[u][1] = len[u][0];
            len[u][0] = l;
        }
        else if (l > len[u][1])
        {
            len[u][1] = l;
        }
    };

    long long ans = 0;

    while (!q.empty()) 
    {
        int u = q.front();
        q.pop();
        ans = max(ans, len[u][0] + arr[u]);
        ans = max(ans, len[u][0] + len[u][1] + arr[u]);
        len[u][0] += arr[u];
        len[u][1] += arr[u];
        for (int i : G[u])
        { 
            if (deg[i] >= 2) 
            {
                insert(i, len[u][0]);
            }
            if (--deg[i] == 1) 
            {
                q.push(i);
            }
        }
    }
    vector<int> cyc;
    for (int i = 1; i <= n; i++)
    {
        if (deg[i] == 2) 
        {
            cyc.push_back(i), deg[i] = 1;
            for (int x = i;;) 
            {
                int flag = 0;
                for (int j : G[x])
                {
                    if (deg[j] == 2) 
                    {
                        cyc.push_back(j);
                        deg[j] = 1;
                        x = j;
                        flag = 1;
                        break;
                    }
                }
                if (!flag)
                {
                    break;
                }
            }
            break;
        }
    }
    // max(len[cyc[u]][0] + len[cyc[v]][0] + sum[v] - sum[u] + arr[cyc[u]]), u < v
    deque<int> dq;
    for (int i = 0; i < 2 * int(cyc.size()); i++) 
    {
        int u = cyc[i % int(cyc.size())];
        ans = max(ans, len[u][0] + arr[u]);
        ans = max(ans, len[u][0] + len[u][1] + arr[u]);
        sum[i] = arr[u];
        if (i) 
        { 
            int prv = cyc[(i - 1) % int(cyc.size())];
            sum[i] += sum[i - 1];
            while (!dq.empty() && len[cyc[dq.back() % int(cyc.size())]][0] - sum[dq.back()] + arr[cyc[dq.back() % int(cyc.size())]] < len[prv][0] - sum[i - 1] + arr[prv])
            {
                dq.pop_back();
            }
            dq.push_back(i - 1);
        }
        while (!dq.empty() && i - dq[0] >= int(cyc.size()))
        {
            dq.pop_front();
        }
        if (!dq.empty()) 
        {
            ans = max(ans, len[u][0] + sum[i] + len[cyc[dq.front() % int(cyc.size())]][0] - sum[dq.front()] + arr[cyc[dq.front() % int(cyc.size())]]);
        }
    }

    cout << ans << "\n";
}
