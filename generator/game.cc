#include<algorithm>
#include<numeric>
#include<random>
#include<string>
#include<unordered_set>
#include<utility>
#include<vector>
#include<cstdio>
using namespace std;
using Pii = pair<int, int>;
using Unif = uniform_int_distribution<>;

constexpr int N[] = {100'000, 100, 100'000, 100'000, 100'000};
constexpr int A_MAX = 1'000'000'000;
constexpr int A_MIN[] = {-A_MAX, -A_MAX, -A_MAX, 0, -A_MAX};
mt19937_64 Rng;

struct Gen{
   Gen() = default;
   constexpr void next() noexcept{
      ++subtask; file = 0;
   }
   int get_subtask() const noexcept{
      return subtask;
   }
   void gen(vector<Pii> const &e, vector<int> const &a, string const &comment = "random"){
      static char fn_prefix[20];
      sprintf(fn_prefix, "%d_%02d_", subtask, ++file);
      FILE *fout = fopen((fn_prefix+comment+".in").data(), "wb");
      fprintf(fout, "%zu %zu\n", a.size(), e.size());
      for(auto ei: e){
         int u = ei.first, v = ei.second;
         if(u > v){
            swap(u, v);
         }
         fprintf(fout, "%d %d\n", u, v);
      }
      for(size_t i=0; i<a.size(); ++i){
         fprintf(fout, "%d%c", a[i], " \n"[i+1==a.size()]);
      }
      fclose(fout);
   }
private:
   int subtask = 0, file = 0;
};

vector<int> RandomSeq(int n, int r_min, int r_max, int seed){
   Rng.seed(seed);
   vector<int> res(n);
   for(int &ri: res){
      ri = Unif(r_min, r_max)(Rng);
   }
   return res;
}

vector<Pii> Path(int n, int seed){
   Rng.seed(seed);
   vector<int> id(n);
   iota(id.begin(), id.end(), 1);
   shuffle(id.begin(), id.end(), Rng);
   vector<Pii> e(n-1);
   for(int i=0; i<=n-2; ++i){
      e[i] = {id[i], id[i+1]};
   }
   shuffle(e.begin(), e.end(), Rng);
   return e;
}

vector<Pii> BinaryTree(int n, int seed){
   Rng.seed(seed);
   vector<int> id(n);
   iota(id.begin(), id.end(), 1);
   shuffle(id.begin(), id.end(), Rng);
   vector<Pii> e(n-1);
   for(int i=0; i<=n-2; ++i){
      e[i] = {id[i+1], id[i/2]};
   }
   shuffle(e.begin(), e.end(), Rng);
   return e;
}

vector<Pii> Star(int n, int seed){
   Rng.seed(seed);
   vector<int> id(n);
   iota(id.begin(), id.end(), 1);
   shuffle(id.begin(), id.end(), Rng);
   vector<Pii> e(n-1);
   for(int i=0; i<=n-2; ++i){
      e[i] = {id[0], id[i+1]};
   }
   return e;
}

vector<Pii> RandomTree(int n, int seed){
   Rng.seed(seed);
   vector<int> id(n);
   iota(id.begin(), id.end(), 1);
   shuffle(id.begin(), id.end(), Rng);
   vector<Pii> e(n-1);
   for(int i=0; i<=n-2; ++i){
      e[i] = {id[i+1], id[Unif(0, i)(Rng)]};
   }
   shuffle(e.begin(), e.end(), Rng);
   return e;
}

vector<Pii> Cycle(int n, int seed){
   Rng.seed(seed);
   vector<int> id(n);
   iota(id.begin(), id.end(), 1);
   shuffle(id.begin(), id.end(), Rng);
   vector<Pii> e(n);
   for(int i=0; i<=n-2; ++i){
      e[i] = {id[i], id[i+1]};
   }
   e.back() = {id[0], id[n-1]};
   shuffle(e.begin(), e.end(), Rng);
   return e;
}

vector<Pii> RandomJelly(int n, int seed){
   Rng.seed(seed);
   vector<int> f(n), djs(n, -1);
   bool cycle = false;
   auto find = [&djs](int i) noexcept{
      int r = i;
      while(djs[r] != -1){
         r = djs[r];
      }
      while(i != r){
         int j = djs[i];
         djs[i] = r;
         i = j;
      }
      return r;
   };
   for(int i=0; i<=n-1; ++i){
      do{ // will be infinite if f[i] = n-1 for all i in 0..n-2
         f[i] = Unif(0, n-1)(Rng);
      }while((f[i]<=i && f[f[i]]==i) || (cycle && find(i)==find(f[i])));
      int r = find(i), s = find(f[i]);
      if(r == s){
         cycle = true;
      }else{
         djs[r] = s;
      }
   }
   vector<int> id(n);
   iota(id.begin(), id.end(), 1);
   shuffle(id.begin(), id.end(), Rng);
   vector<Pii> e(n);
   for(int i=0; i<=n-1; ++i){
      e[i] = {id[i], id[f[i]]};
   }
   shuffle(e.begin(), e.end(), Rng);
   return e;
}

int main(){
   Gen g;

   // subtask 1
   g.next();
   g.gen({{6, 8}, {3, 6}, {2, 6}, {1, 3}, {1, 2}, {1, 4}, {1, 5}, {5, 7}}, {-1, 2, 3, -10, -3, 0, 4, 2}, "sample1");
   g.gen({{1, 2}}, {-1, -10}, "sample2");
   g.gen({}, {10}, "single_point");
   g.gen(Path(N[1], 0), RandomSeq(N[1], A_MIN[1], A_MAX, 0), "path_n1");
   g.gen(BinaryTree(N[1], 58), RandomSeq(N[1], A_MIN[1], A_MAX, 58), "binary_tree_n1");
   g.gen(Star(N[1], 514), RandomSeq(N[1], A_MIN[1], A_MAX, 514), "star_n1");
   g.gen(RandomTree(N[1], 689), RandomSeq(N[1], A_MIN[1], A_MAX, 689), "random_tree_n1");
   g.gen(Cycle(N[1], 4649), RandomSeq(N[1], A_MIN[1], A_MAX, 4649), "cycle_n1");
   g.gen(RandomJelly(N[1], 7122), RandomSeq(N[1], A_MIN[1], A_MAX, 7122), "random_jellyfish_n1");

   // subtask 2
   g.next();
   g.gen({{1, 2}}, {-1, -10}, "sample2");
   g.gen(Path(N[2], 38), RandomSeq(N[2], A_MIN[2], A_MAX, 38), "path_n2");
   g.gen(BinaryTree(N[2], 78), RandomSeq(N[2], A_MIN[2], A_MAX, 78), "binary_tree_n2");
   g.gen(Star(N[2], 87), RandomSeq(N[2], A_MIN[2], A_MAX, 87), "star_n2");
   for(int T=5; T-->0; ){
      g.gen(RandomTree(N[2]-T, 98+T), RandomSeq(N[2]-T, A_MIN[2], A_MAX, 98+T), "random_tree");
   }

   // subtask 3
   g.next();
   g.gen(Path(N[3], 0), RandomSeq(N[3], A_MIN[3], A_MAX, 0), "path_n3");
   g.gen(BinaryTree(N[3], 58), RandomSeq(N[3], A_MIN[3], A_MAX, 58), "binary_tree_n3");
   g.gen(Star(N[3], 514), RandomSeq(N[3], A_MIN[3], A_MAX, 514), "star_n3");
   g.gen(RandomTree(N[3], 689), RandomSeq(N[3], A_MIN[3], A_MAX, 689), "random_tree_n3");
   g.gen(Cycle(N[3], 4649), RandomSeq(N[3], A_MIN[3], A_MAX, 4649), "cycle_n3");
   for(int T=5; T-->0; ){
      g.gen(RandomJelly(N[3]-T, 7122^T), RandomSeq(N[3]-T, A_MIN[3], A_MAX, 7122^T), "random_jellyfish");
   }

   // subtask 4
   g.next();
   g.gen(Cycle(N[4], 4649), RandomSeq(N[4], A_MIN[4], A_MAX, 4649), "cycle_n4");
   for(int T=5; T-->0; ){
      g.gen(RandomJelly(N[4]-T, 7122-T), RandomSeq(N[4]-T, A_MIN[4], A_MAX, 7122-T), "random_jellyfish");
   }
}
