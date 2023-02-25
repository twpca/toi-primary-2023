#include<bits/stdc++.h>
#include "testlib.h"
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
using namespace std;
using LL = long long;

constexpr int SUBTASKS = 6;
constexpr int MN_NK = 1;
constexpr int MX_N[SUBTASKS+1] = {200'000, 20, 10'000, 10'000, 200'000, 200'000, 200'000};
constexpr LL  MX_K[SUBTASKS+1] = {
    (LL)MX_N[0] * (MX_N[0]+1) / 2,
    (LL)MX_N[1] * (MX_N[1]+1) / 2,
    200'000,
    (LL)MX_N[3] * (MX_N[3]+1) / 2,
    200'000,
    (LL)MX_N[5] * (MX_N[5]+1) / 2,
    (LL)MX_N[6] * (MX_N[6]+1) / 2
};
constexpr int MN_W[SUBTASKS+1] = {-1'000'000'000, -1'000'000'000, -1'000'000'000, -1'000'000'000, -1'000'000'000, -100, -1'000'000'000};
constexpr int MX_W[SUBTASKS+1] = { 1'000'000'000,  1'000'000'000,  1'000'000'000,  1'000'000'000,  1'000'000'000,  100,  1'000'000'000};

int subtask(int argc, char* argv[]) {
    for (int i=1; i<argc; i++) {
        if (!strcmp("--testcase", argv[i-1])) {
            int subtask = atoi(argv[i]);
            assert(0 <= subtask && subtask <= SUBTASKS);
            return subtask;
        }
    }
    assert(0);
    return -1;
}

int main(int argc,char* argv[]) {
    registerValidation(argc, argv);
    int s = subtask(argc, argv);

    int n = inf.readInt(MN_NK, MX_N[s], "n"); inf.readChar(' ');
    LL k = inf.readLong(MN_NK, MX_K[s], "k"); inf.readChar('\n');
    ensuref(k <= (LL)n*(n+1)/2LL, "k should <= k*(k+1)/2");
    REP(i,1,n) {
        inf.readInt(MN_W[s], MX_W[s], "w_i");
        if (i<n) {
            inf.readChar(' ');
        } else {
            inf.readChar('\n');
        }
    }
    inf.readEof();
    return 0;
}
