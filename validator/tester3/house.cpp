#include<bits/stdc++.h>
#include "testlib.h"
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
using namespace std;
using PII = pair<int,int>;
constexpr int SUBTASKS = 3;
constexpr int MN_NM = 1;
constexpr int MX_N[SUBTASKS+1] = {100'000, 2, 100, 100'000};
constexpr int MX_M[SUBTASKS+1] = {1'000, 1'000, 1'000, 1'000};

constexpr int MN_XY = -1'000'000'000;
constexpr int MX_XY =  1'000'000'000;

constexpr int MN_C = 0;
constexpr int MX_C = 1'000'000'000;

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
    int n = inf.readInt(MN_NM, MX_N[s], "n"); inf.readChar(' ');
    int m = inf.readInt(MN_NM, MX_M[s], "m"); inf.readChar('\n');

    map<PII, bool> vis;
    REP(i,1,n) {
        int x = inf.readInt(MN_XY, MX_XY, "x1_i"); inf.readChar(' ');
        int y = inf.readInt(MN_XY, MX_XY, "y1_i"); inf.readChar(' ');
        int c = inf.readInt(MN_C, MX_C, "c_i");    inf.readChar('\n');

        PII pos = PII(x, y);
        ensuref(vis.count(pos)==0, "(%d, %d) duplicated", x, y);
        vis[pos] = true;
    }
    REP(i,1,m) {
        int x = inf.readInt(MN_XY, MX_XY, "x1_i"); inf.readChar(' ');
        int y = inf.readInt(MN_XY, MX_XY, "y1_i"); inf.readChar('\n');

        PII pos = PII(x, y);
        ensuref(vis.count(pos)==0, "(%d, %d) duplicated", x, y);
        vis[pos] = true;
    }
    inf.readEof();
    return 0;
}
