#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;
using T = tuple<int,int,int>;
// xx, yy, xy
constexpr int cpair_to_pos(char a, char b) {
    assert(a == 'X' || a == 'Y');
    assert(b == 'X' || b == 'Y');
    if (a == 'X' && b == 'X') return 0;
    if (a == 'Y' && b == 'Y') return 1;
    return 2;
}
T get_abc(const string &x) {
    int res[3] = {0, 0, 0};
    int len = x.length();
    for (int i=2; i<len; i++) {
        int pos = cpair_to_pos(x[i], x[i-2]);
        res[pos] += 1;
    }
    res[cpair_to_pos(x[0], x[len-2])] += 1;
    res[cpair_to_pos(x[1], x[len-1])] += 1;
    return T(res[0], res[1], res[2]);
}
int get_unstableness(const string &x) {
    int res = 0;
    int cur = 0;
    int len = x.length();
    for (int i=0; i<len; i++) {
        if (i!=0 && x[i]!=x[i-1]) {
            cur = 0;
        }
        cur++;
        res = max(res, cur);
    }

    if (x[0] == x[len-1]) {
        int l = 0;
        int r = len - 1;
        while (l < len-1 && x[l] == x[l+1]) l++;
        while (r > 0 && x[r] == x[r-1]) r--;
        int cnt = min(len, (l+1) + (len-r));
        res = max(res, cnt);
    }
    return res;
}

string readOutputM(int len) {
    string f = "[XY]{" + to_string(len) + ", " + to_string(len) + "}";
    return ouf.readToken(f);
}

int main(int argc, char *argv[]) {
    inf.maxFileSize = 1024 * 1024 * 1024; // 1024MB
    setName("molecule special judge");
    registerTestlibCmd(argc, argv);

    // read inputs
    int a = inf.readInt();
    int b = inf.readInt();
    int c = inf.readInt();
    if (a + b + c <= 2) {
        quitf(_fail, "testdata validation failed: a+b+c <= 2");
    }

    // read ans
    int k_ans = ans.readInt();

    // read output
    int k_out = ouf.readInt(-1, a+b+c);

    // verify no answer
    if (k_ans == -1) {
        if (k_out == -1) {
            quitf(_ok, "OK");
        } else {
            string m = readOutputM(a+b+c);
            if (get_abc(m) == make_tuple(a, b, c)) { // unreachable?
                quitf(_ok, "wow you found a feasible solution");
            }
            quitf(_wa, "k_ans=%d, k_out=%d", k_ans, k_out);
        }
    }
    if (k_out == -1) {
        quitf(_wa, "k_ans=%d, k_out=%d", k_ans, k_out);
    }


    string m = readOutputM(a+b+c);
    // verify (a, b, c)
    if (get_abc(m) != make_tuple(a, b, c)) {
        quitf(_wa, "(a,b,c) of %s is not = (%d,%d,%d)", m.c_str(), a, b, c);
    }
    // verify unstableness
    if (get_unstableness(m) != k_out) {
        quitf(_wa, "unstableness of %s is not %d", m.c_str(), k_out);
    }

    if (k_out < k_ans) {
        quitf(_ok, "wow your answer is better"); // unreachable?
    } else if (k_out == k_ans) {
        quitf(_ok, "optimal solution");
    }

    double score = round(1000.0 / (double)(1 + min(19, k_out - k_ans))) / 1000.0;
    fprintf(stdout, "%.10f\n", score); // score for CMS
    quitf(_pc(int(score*200)), "partial"); // testlib style partial, score is ranged [0, 200]
}
