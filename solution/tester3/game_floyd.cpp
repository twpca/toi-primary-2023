// O(n^3)
// floyd warshall
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M 105
using namespace std;
using LL = long long;
constexpr LL INFMIN = -(1LL << 60);

int n, m, w[M], xp[M*M], yp[M*M];
LL dis[M][M];

int main()
{
    while (~scanf("%d %d", &n, &m)) {
        REP(i,1,m) scanf("%d %d", &xp[i], &yp[i]);
        REP(i,1,n) scanf("%d", &w[i]);

        REP(i,1,n) REP(j,1,n) dis[i][j] = INFMIN;
        REP(i,1,n) dis[i][i] = 0;
        REP(i,1,m) {
            int x = xp[i];
            int y = yp[i];
            dis[y][x] = max(dis[y][x], (LL)w[x]);
            dis[x][y] = max(dis[x][y], (LL)w[y]);
        }
        REP(k,1,n) REP(i,1,n) REP(j,1,n) dis[i][j] = max(dis[i][j], dis[i][k] + dis[k][j] + w[k]);

        LL ans = INFMIN;
        REP(i,1,n) REP(j,1,n) ans = max(ans, dis[i][j] + w[i]);
        printf("%lld\n", ans);
    }
    return 0;
}
