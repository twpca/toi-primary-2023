// O(abc * (a+b+c))
// Expect: subtask1 + subtask2
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M
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

class DPSolver {
    static constexpr int INF = 1'000'000'000;
    int dp_size;
    // dp_size=40, csteps=2'631'623
    // dp_size=50, csteps=6'393'102
    // dp_size=60, csteps=13'211'133

    // s[0] == 'X'
    // s[1], XX, YY, XY, suffix_continuous_cnt, s[-1]
    // int dp[2][SIZE+1][SIZE+1][SIZE+1][3*SIZE+1][2];
    static constexpr int ARG_SIZE = 6;
    int arg_mult[ARG_SIZE];
    unordered_map<int, int> dp, fr;

    int compress(int a, int b, int c, int d, int e, int f) {
        int ar[ARG_SIZE] = {a, b, c, d, e, f};
        int res = 0;
        REP(i,0,ARG_SIZE-1) {
            res *= arg_mult[i];
            res += ar[i];
        }
        return res;
    }

    void decompress(int x, int &a, int &b, int &c, int &d, int &e, int &f) {
        int res[ARG_SIZE];
        for (int i=ARG_SIZE-1; i>=0; i--) {
            res[i] = x % arg_mult[i];
            x /= arg_mult[i];
        }
        a = res[0];
        b = res[1];
        c = res[2];
        d = res[3];
        e = res[4];
        f = res[5];
    }

    int ipair_to_pos(int a, int b) {
        return cpair_to_pos('X'+a, 'X'+b);
    }

    void fill_dp_table() {
        queue<int> q;
        // XX
        dp[compress(0, 2, 0, 0, 2, 0)] = 2;
        q.push(compress(0, 2, 0, 0, 2, 0));
        // XY
        dp[compress(1, 1, 1, 0, 1, 1)] = 1;
        q.push(compress(1, 1, 1, 0, 1, 1));

        // S = X, f2, ..., b2, b1, b0
        while (!q.empty()) {
            int f2, a, b, c, suf, b1;
            int key = q.front();
            q.pop();
            decompress(key, f2, a, b, c, suf, b1);

            int cur_dp = dp[compress(f2, a, b, c, suf, b1)];
            int b2 = suf>1 ? b1 : 1-b1;

            REP(b0, 0, 1) {
                int cnt[3] = {a, b, c};
                cnt[ipair_to_pos(0, b2)] -= 1;
                cnt[ipair_to_pos(f2, b1)] -= 1;
                cnt[ipair_to_pos(b2, b0)] += 1;
                cnt[ipair_to_pos(0, b1)] += 1;
                cnt[ipair_to_pos(f2, b0)] += 1;
                if (*max_element(cnt, cnt+3) > dp_size) continue;

                int ns = (b1 == b0) ? suf+1 : 1;
                int nv = max(cur_dp, ns);
                int nkey = compress(f2, cnt[0], cnt[1], cnt[2], ns, b0);
                int &nxt_dp = dp[nkey];
                if (nxt_dp==0 || nxt_dp>nv) {
                    if (nxt_dp == 0) q.push(nkey);
                    nxt_dp = nv;
                    fr[nkey] = key;
                }
            }
        }
    }

public:
    void build(int size) {
        dp_size = size + 1;
        arg_mult[0] = 2;
        arg_mult[1] = dp_size+1;
        arg_mult[2] = dp_size+1;
        arg_mult[3] = dp_size+1;
        arg_mult[4] = 3*dp_size+1;
        arg_mult[5] = 2;
        fill_dp_table();
    }
    pair<int, string> get_unstableness(int a, int b, int c) {
        // only X, only Y
        if (b==0 && c==0) return make_pair(a, string(a, 'X'));
        if (a==0 && c==0) return make_pair(b, string(b, 'Y'));

        int res = INF;
        int state = -1;
        REP(f2, 0, 1) REP(suf, 1, a+b+c) {
            int curdp = dp[compress(f2, a, b, c, suf, 1)];
            if (curdp!=0 && res>curdp) {
                res = curdp;
                state = compress(f2, a, b, c, suf, 1);
            }
        }
        if (res == INF) return make_pair(-1, "");

        string res2 = "";
        int f2, suf, b1;
        while (state) {
            decompress(state, f2, a, b, c, suf, b1);
            res2 += char('X' + b1);
            state = fr[state];
        }
        res2 += "X";
        reverse(res2.begin(), res2.end());
        return make_pair(res, res2);
    }
};
DPSolver dp;

int main()
{
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    dp.build(max(max(a, b), c));

    int a1;
    string a2;
    tie(a1, a2) = dp.get_unstableness(a, b, c);
    if (a1 == -1) {
        puts("-1");
    } else {
        printf("%d\n%s\n", a1, a2.c_str());
    }
    return 0;
}
