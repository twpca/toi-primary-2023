#include <iostream>
#include <algorithm>
using namespace std;

const long long INF = 9e18;
const int MAXN = 100005;
const int MAXM = 1005;

long long dis(int *a, int *b)
{
    long long res = 0;
    for (int i = 0; i < 2; i++)
    {
        res += (long long)(a[i] - b[i]) * (a[i] - b[i]);
    }
    return res;
}

int ans[MAXN];
int arr[MAXN][3], brr[MAXM][2];
long long min_dis[MAXN];

int main() 
{
    ios::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i][0] >> arr[i][1] >> arr[i][2];
    }
    for (int i = 1; i <= m; i++)
    {
        cin >> brr[i][0] >> brr[i][1];
    }
    for (int i = 1; i <= n; i++)
    {
        ans[i] = i;
        min_dis[i] = INF;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            min_dis[i] = min(min_dis[i], dis(arr[i], brr[j]));
        }
    }
    sort(ans + 1, ans + n + 1, [&](int a, int b) 
    {
        if (min_dis[a] != min_dis[b])
        { 
            return min_dis[a] < min_dis[b];
        }
        if (arr[a][2] != arr[b][2]) 
        { 
            return arr[a][2] < arr[b][2];
        }
        return a < b;
    });
    for (int i = 1; i <= n; i++)
    {
        cout << ans[i] << "\n";
    }
}
