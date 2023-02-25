// O(n log n + n log w)
// Expect: AC
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M 200005
using namespace std;
using LL = long long;
int n;
LL k, w[M];
bool test(LL x) {
    LL cnt = 0;
    REP(i,1,n) if (2*w[i] >= x) cnt++;

    int pos = n;
    REP(i,1,n) {
        while (pos-1 >= 1 && w[pos-1] + w[i] >= x) pos--;
        if (w[pos] + w[i] >= x) {
            if (pos > i) {
                cnt += n - pos + 1;
            } else {
                cnt += n - i;
            }
        }
    }
    return cnt >= k;
}
int main()
{
    while (~scanf("%d %lld", &n, &k)) {
        REP(i,1,n) scanf("%lld", &w[i]);
        sort(w+1, w+n+1);

        LL INF = 2'000'000'000;
        LL ok = -INF-1;
        LL ng = INF+1;
        LL mid;
        while (abs(ok-ng) > 1) {
            mid = (ok + ng) / 2;
            if (test(mid)) ok = mid;
            else ng = mid;
        }

        LL ans = ok;
        if (ans%2) {
            printf("%lld\n%d\n", ans, 2);
        } else {
            printf("%lld\n%d\n", ans/2, 1);
        }
    }
    return 0;
}
