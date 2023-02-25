#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 10005;

int arr[MAXN];
int val[MAXN * MAXN];

int main() 
{
    ios::sync_with_stdio(0), cin.tie(0);
    int n, k, tp = 0;
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = i; j <= n; j++)
        {
            val[++tp] = arr[i] + arr[j];
        }
    }
    nth_element(val + 1, val + k, val + tp + 1, greater<int>());
    int ans = val[k];
    if (ans % 2 == 0)
    {
        cout << ans / 2 << "\n1\n";
    }
    else
    {
        cout << ans << "\n2\n";
    }
}
