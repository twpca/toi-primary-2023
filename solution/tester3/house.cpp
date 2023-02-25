// O(nm + n log n)
// Expect: AC
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M 100005
using namespace std;
using LL = long long;
constexpr LL INF = LLONG_MAX;
int n, m;
int a[M], b[M], r[M];
int c[M], d[M];
int ans[M];
LL nearest[M];
LL dis(int x, int y) {
    return (LL)(a[x] - c[y]) * (a[x] - c[y]) + (LL)(b[x] - d[y]) * (b[x] - d[y]);
}
bool comp(int x, int y) {
    if (nearest[x] != nearest[y]) {
        return nearest[x] < nearest[y];
    }
    if (r[x] != r[y]) {
        return r[x] < r[y];
    }
    return x < y;
}
int main()
{
    while (~scanf("%d %d", &n, &m)) {
        REP(i,1,n) scanf("%d %d %d", &a[i], &b[i], &r[i]);
        REP(i,1,m) scanf("%d %d", &c[i], &d[i]);
        REP(i,1,n) {
            nearest[i] = INF;
            REP(j,1,m) nearest[i] = min(nearest[i], dis(i, j));
        }

        REP(i,1,n) ans[i] = i;
        sort(ans+1, ans+n+1, comp);
        REP(i,1,n) printf("%d\n", ans[i]);
    }
    return 0;
}
