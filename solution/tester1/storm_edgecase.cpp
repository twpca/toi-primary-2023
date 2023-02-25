#include <iostream>
#include <algorithm>
using namespace std;

const long long C = 2e9;

long long arr[200005];

int main() 
{
    ios::sync_with_stdio(0), cin.tie(0);
    int n;
    long long k;
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }
    sort(arr + 1, arr + n + 1);

    auto cal = [&](long long mid) 
    {
        long long res = 0;
        for (int i = 1, j = n; i <= n; i++) 
        {
            if (j < i) 
            { 
                j++;
            }
            while (j >= i && arr[i] + arr[j] >= mid) 
            { 
                j--;
            }
            res += n - j;
        }
        return res;
    };

    long long l = -C, r = C;
    while (r - l > 1) 
    {
        long long mid = (l + r) / 2;
        if (cal(mid) >= k) 
        {
            l = mid;
        }
        else
        {
            r = mid;
        }
    }
    if (l % 2 == 0) 
    {
        cout << l / 2 << "\n1\n";
    }
    else
    {
        cout << l << "\n2\n";
    }
}
