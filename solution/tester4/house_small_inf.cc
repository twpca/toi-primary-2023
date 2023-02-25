#include<algorithm>
#include<numeric>
#include<tuple>
#include<vector>
#include<cstdio>
using namespace std;
using i64 = long long;
constexpr i64 INF = 5'000'000'000'000'000'000;

int main(){
   int n, m;
   scanf("%d%d", &n, &m);
   vector<int> a(n), b(n), r(n), c(m), d(m);
   for(int i=0; i<=n-1; ++i){
      scanf("%d%d%d", a.data()+i, b.data()+i, r.data()+i);
   }
   for(int i=0; i<=m-1; ++i){
      scanf("%d%d", c.data()+i, d.data()+i);
   }
   vector<i64> dis(n, INF);
   for(int i=0; i<=n-1; ++i){
      for(int j=0; j<=m-1; ++j){
         dis[i] = min(dis[i], ((i64)a[i]-c[j])*(a[i]-c[j])+((i64)b[i]-d[j])*(b[i]-d[j]));
      }
   }
   vector<int> si(n);
   iota(si.begin(), si.end(), 0);
   sort(si.begin(), si.end(), [&dis, &r](int i, int j) noexcept{
      return make_tuple(dis[i], r[i], i) < make_tuple(dis[j], r[j], j);
   });
   for(int sii: si){
      printf("%d\n", sii+1);
   }
}
