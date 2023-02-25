// O(n^2 log k)
// Expect: subtask 1 AC
//         subtask 2 AC(??)
//         subtask 3, 4 TLE
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M 200005
using namespace std;
using LL = long long;
int n, w[M];
LL k;
priority_queue<int,vector<int>,greater<int>> pq;

void add(int x) {
    if ((int)pq.size() < k) {
        pq.push(x);
    } else if ((int)pq.size()>=k && pq.top()<x) {
        pq.pop();
        pq.push(x);
    }
}
int main()
{
    while (~scanf("%d %lld", &n, &k)) {
        pq = priority_queue<int,vector<int>,greater<int>> ();
        REP(i,1,n) scanf("%d", &w[i]);
        REP(i,1,n) add(2 * w[i]);
        REP(i,1,n) REP(j,i+1,n) add(w[i] + w[j]);

        int ans = pq.top();
        if (ans%2) {
            printf("%d\n%d\n", ans, 2);
        } else {
            printf("%d\n%d\n", ans/2, 1);
        }
    }
    return 0;
}
