#include<algorithm>
#include<random>
#include<unordered_set>
#include<vector>
#include<cassert>
#include<cstdio>
#include<cstdlib>
using namespace std;
using i64 = long long;
using Unif = uniform_int_distribution<>;

constexpr int MAX_X = 1'000'000'000;
constexpr int MIN_X = -1'000'000'000;
constexpr int DX = 10'000;
constexpr int R = 1'000'000'000;

struct Pt{
   int x, y;
   Pt() = default;
   constexpr Pt(int a, int b) noexcept: x(a), y(b){}
};
bool operator==(Pt p, Pt q) noexcept{
   return p.x==q.x && p.y==q.y;
}
template<> struct std::hash<Pt>{
   size_t operator()(Pt p) const noexcept{
      return ((i64)p.x-MIN_X)<<32 | (p.y-MIN_X);
   }
};

void GenerateExtreme(int n, int m, int seed){
   mt19937_64 rng(seed);
   unordered_set<Pt> hs;
   vector<pair<Pt, int>> house(n);
   for(int i=0; i<=n-1; ++i){
      house[i].first = {MAX_X-n+i+1, MAX_X-i};
      house[i].second = Unif(0, R)(rng);
      hs.insert(house[i].first);
   }
   shuffle(house.begin(), house.end(), rng);
   vector<Pt> sta(m);
   sta[0] = {MIN_X, MIN_X};
   hs.insert(sta[0]);
   for(int i=1; i<=m-1; ++i){
      do{
         sta[i].x = MIN_X+Unif(0, DX)(rng);
         sta[i].y = MIN_X+Unif(0, DX)(rng);
      }while(!hs.insert(sta[i]).second);
   }
   shuffle(sta.begin(), sta.end(), rng);
   printf("%d %d\n", n, m);
   for(auto hi: house){
      printf("%d %d %d\n", hi.first.x, hi.first.y, hi.second);
   }
   for(auto stai: sta){
      printf("%d %d\n", stai.x, stai.y);
   }
}

int main(int argc, char **argv){
   assert(argc == 4);
   GenerateExtreme(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
}
