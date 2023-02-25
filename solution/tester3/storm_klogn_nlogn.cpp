// O(n log n + k log n)
// Expect: subtask 1,2,4 AC
//         subtask 3     AC(?)
//         subtask 5,6 TLE
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M 200005
using namespace std;
using LL = long long;
using T = tuple<int,int,int>;
int n, w[M];
LL k;
priority_queue<T> pq;
int main()
{
    while (~scanf("%d %lld", &n, &k)) {
        pq = priority_queue<T> ();
        REP(i,1,n) scanf("%d", &w[i]);
        sort(w+1, w+n+1, greater<int> ());

        // (1, 1), (2, 2), (3, 3) ...
        // (1, 2), (2, 3), (3, 4) ...
        // (1, 3), (2, 4), (3, 5) ...
        // (1, 4), (2, 5), (3, 6) ...
        REP(i,0,n-1) {
            pq.emplace(w[1] + w[1+i], 1, 1+i);
        }
        REP(i,1,k-1) {
            int x, y, z;
            tie(x, y, z) = pq.top();
            pq.pop();

            y++;
            z++;
            if (z <= n) pq.emplace(w[y] + w[z], y, z);
        }

        int ans = get<0> (pq.top());
        if (ans%2) {
            printf("%d\n%d\n", ans, 2);
        } else {
            printf("%d\n%d\n", ans/2, 1);
        }
    }
    return 0;
}
