#include<algorithm>
#include<vector>
#include<climits>
#include<cstdio>
using namespace std;
using i64 = long long;
using pii = pair<i64, i64>;

pii dfs(vector<int> const *g, vector<bool> const &incyc, int const *a, int u, int p){
   i64 res = LLONG_MIN, max1 = 0, max2 = 0;
   for(int v: g[u]) if(!incyc[v] && v!=p){
      auto q = dfs(g, incyc, a, v, u);
      res = max(res, q.first);
      if(q.second > max2){
         max2 = q.second;
         if(max2 > max1){
            swap(max1, max2);
         }
      }
   }
   res = max(res, a[u]+max1+max2);
   return {res, a[u]+max1};
}

bool find_cycle(vector<int> const *g, vector<bool> &incyc, vector<bool> &vis, vector<int> &cyc, int u, int p){
   vis[u] = true;
   cyc.push_back(u);
   for(int v: g[u]){
      if(v == p) continue;
      if(vis[v]){
         cyc.erase(cyc.begin(), find(cyc.begin(), cyc.end(), v));
         for(int w: cyc){
            incyc[w] = true;
         }
         return true;
      }
      if(find_cycle(g, incyc, vis, cyc, v, u)){
         return true;
      }
   }
   cyc.pop_back();
   return false;
}

int main(){
   int n, m;
   scanf("%d%d", &n, &m);
   vector<vector<int>> g(n);
   for(int i=1; i<=m; ++i){
      int u, v;
      scanf("%d%d", &u, &v);
      --u; --v;
      g[u].push_back(v);
      g[v].push_back(u);
   }
   vector<int> a(n);
   for(int i=0; i<=n-1; ++i){
      scanf("%d", a.data()+i);
   }
   vector<bool> incyc(n);
   if(m == n-1){
      printf("%lld\n", dfs(g.data(), incyc, a.data(), 0, 0).first);
      return 0;
   }
   vector<bool> vis(n);
   vector<int> cyc;
   find_cycle(g.data(), incyc, vis, cyc, 0, 0);
   i64 ans = LLONG_MIN, s = 0;
   vector<i64> b(cyc.size()), dq_bisi;
   vector<int> dq_i;
   for(size_t i=0; i<cyc.size(); ++i){
      int u = cyc[i];
      auto p = dfs(g.data(), incyc, a.data(), u, u);
      ans = max(ans, p.first);
      s += a[u];
      b[i] = p.second;
      while(!dq_bisi.empty() && dq_bisi.back() <= b[i]-s){
         dq_i.pop_back();
         dq_bisi.pop_back();
      }
      dq_i.push_back(i);
      dq_bisi.push_back(b[i]-s);
   }
   size_t l = 0;
   for(size_t i=0; i<cyc.size(); ++i){
      if(dq_i[l] == i){
         ++l;
      }
      int u = cyc[i];
      ans = max(ans, b[i]+s+dq_bisi[l]);
      s += a[u];
      while(dq_bisi.size()>l && dq_bisi.back() <= b[i]-s){
         dq_i.pop_back();
         dq_bisi.pop_back();
      }
      dq_i.push_back(cyc.size()+i);
      dq_bisi.push_back(b[i]-s);
   }
   printf("%lld\n", ans);
}
