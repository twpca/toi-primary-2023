#include"testlib.h"
#include<cassert>
#include<cstdio>
#include<cstring>
using namespace std;

constexpr int N_SUBTASKS = 4;
constexpr int N_MIN = 1;
constexpr int N_MAX[] = {100'000, 100, 100'000, 100'000, 100'000};
constexpr bool TREE[] = {0, 0, 1, 0, 0};
constexpr int A_MAX = 1'000'000'000;
constexpr int A_MIN[] = {-A_MAX, -A_MAX, -A_MAX, 0, -A_MAX};

int get_subtask(int argc, char **argv){
   for(int i=1; i<argc; ++i){
      if(!strcmp(argv[i-1], "--testcase")){
         int res = atoi(argv[i]);
         assert(0<=res && res<=N_SUBTASKS);
         return res;
      }
   }
   abort();
}

int main(int argc, char **argv){
   registerValidation(argc, argv);
   int s = get_subtask(argc, argv);
   int n = inf.readInt(N_MIN, N_MAX[s], "n");
   inf.readChar(' ');
   int m = inf.readInt(n-1, n-TREE[s], "m");
   inf.readChar('\n');
   int cc = n;
   vector<int> djs(n, -1);
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
   for(int i=1; i<=m; ++i){
      char var1[20], var2[20];
      sprintf(var1, "u[%d]", i);
      int ui = inf.readInt(1, n, var1);
      inf.readChar(' ');
      sprintf(var2, "v[%d]", i);
      int vi = inf.readInt(1, n, var2);
      inf.readChar('\n');
      ensuref(ui<vi, "%s = %d, %s = %d, violating u[i] < v[i]", var1, ui, var2, vi);
      --ui; --vi;
      int p = find(ui), q = find(vi);
      if(p != q){
         djs[p] = q; --cc;
      }
   }
   ensuref(cc==1, "the graph is disconnected");
   for(int i=1; i<=n; ++i){
      char var[20];
      sprintf(var, "a[%d]", i);
      inf.readInt(A_MIN[s], A_MAX, var);
      inf.readChar(" \n"[i==n]);
   }
   inf.readEof();
}
