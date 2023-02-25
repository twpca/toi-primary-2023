#include<algorithm>
#include<vector>
#include<cstdio>
using namespace std;
using i64 = long long;

i64 dwim(int const *a, int n, int x){
   i64 res = 0;
   for(int l=0, r=n; l<=n-1; ++l){
      while(r>l && a[l]+a[r-1]>=x){
         --r;
      }
      res += n-r;
      if(l == r) ++r;
   }
   return res;
}

int main(){
   int n; i64 k;
   scanf("%d%lld", &n, &k);
   vector<int> w(n);
   for(int i=0; i<=n-1; ++i){
      scanf("%d", w.data()+i);
   }
   sort(w.begin(), w.end());
   int lb = 2*w[0], ub = 2*w[n-1]+1;
   while((i64)ub-lb > 1){
      int mid = ((i64)ub+lb)/2;
      if(dwim(w.data(), n, mid) >= k){
         lb = mid;
      }else{
         ub = mid;
      }
   }
   if(lb%2 == 0){
      printf("%d\n1\n", lb/2);
   }else{
      printf("%d\n2\n", lb);
   }
}
