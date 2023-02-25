// O(n + w^2)
// Expect: subtask 5 AC
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M 200005
using namespace std;
using LL = long long;
using P = pair<int,LL>;
int n, w[M];
LL k;
unordered_map<int,int> cnt;
vector<P> ord;

int main()
{
    while (~scanf("%d %lld", &n, &k)) {
        cnt.clear();
        REP(i,1,n) {
            scanf("%d", &w[i]);
            cnt[w[i]]++;
        }

        int mn = *min_element(w+1, w+n+1);
        int mx = *max_element(w+1, w+n+1);
        ord.clear();
        REP(i, mn, mx) REP(j, i, mx) {
            if (!cnt.count(i) || !cnt.count(j)) continue;
            LL c;
            if (i == j) {
                c = (LL)cnt[i] * (cnt[i]+1) / 2;
            } else {
                c = (LL)cnt[i] * cnt[j];
            }

            if (c > 0) {
                ord.emplace_back(i+j, c);
            }
        }
        sort(ord.begin(), ord.end(), greater<P> ());

        int ans = -1;
        for (auto i: ord) {
            if (i.second >= k) {
                ans = i.first;
                break;
            } else {
                k -= i.second;
            }
        }

        if (ans%2) {
            printf("%d\n%d\n", ans, 2);
        } else {
            printf("%d\n%d\n", ans/2, 1);
        }
    }
    return 0;
}
