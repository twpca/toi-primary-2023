// O(n^2)
// Expect: subtask 1,2,3 AC
//         subtask 4,5,6 TLE
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M 200005
using namespace std;
using LL = long long;
int n, w[M];
LL k;
vector<int> ar;
int main()
{
    while (~scanf("%d %lld", &n, &k)) {
        ar.clear();
        REP(i,1,n) scanf("%d", &w[i]);
        REP(i,1,n) ar.emplace_back(w[i]*2);
        REP(i,1,n) REP(j,i+1,n) ar.emplace_back(w[i] + w[j]);

        nth_element(ar.begin(), ar.begin() + (k-1), ar.end(), greater<int>());

        int ans = ar[k-1];
        if (ans%2) {
            printf("%d\n%d\n", ans, 2);
        } else {
            printf("%d\n%d\n", ans/2, 1);
        }
    }
    return 0;
}
