#include<bits/stdc++.h>
#include "testlib.h"
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
using namespace std;
using PII = pair<int,int>;
constexpr int SUBTASKS = 4;
constexpr int MN_ABC = 0;
constexpr int MX_ABC[SUBTASKS+1] = {100'000, 100'000, 20, 100'000, 100'000};
constexpr int MN_SUM = 3;
constexpr int MX_SUM[SUBTASKS+1] = {300'000, 15, 300'000, 300'000, 300'000};
constexpr bool B02AGEC[SUBTASKS+1] = {false, false, false, true, false};

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

    int a = inf.readInt(MN_ABC, MX_ABC[s], "a"); inf.readChar(' ');
    int b = inf.readInt(MN_ABC, MX_ABC[s], "b"); inf.readChar(' ');
    int c = inf.readInt(MN_ABC, MX_ABC[s], "c"); inf.readChar('\n');
    inf.readEof();

    ensuref(a+b+c >= MN_SUM,    "a+b+c should >= %d", MN_SUM);
    ensuref(a+b+c <= MX_SUM[s], "a+b+c should <= %d", MX_SUM[s]);

    if (B02AGEC[s]) {
        ensuref(b==0 && 2*a>=c, "b==0 && 2*a>=c should be satisfied");
    }
    return 0;
}
