// Script to verify corectness
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
T get_abc(const string &x) {
    int res[3] = {0, 0, 0};
    int len = x.length();
    REP(i, 2, len-1) {
        int pos = cpair_to_pos(x[i], x[i-2]);
        res[pos] += 1;
    }
    res[cpair_to_pos(x[0], x[len-2])] += 1;
    res[cpair_to_pos(x[1], x[len-1])] += 1;
    return T(res[0], res[1], res[2]);
}
bool noans(int a,int b, int c) {
    if (c%2 == 1) return true;
    if (a==0 && b==0 && c%4==2) return true;
    if (c==0 && a!=b && a!=0 && b!=0) return true;
    if (c==2 && a==b) return true;
    return false;
}

class BruteforceSolver {
    struct Hash {
        static constexpr int HASH_MULTIPLIER = 1111;
        std::size_t operator() (const T& key) const {
            int a, b, c;
            tie(a, b, c) = key;
            return hash<int>() (a*HASH_MULTIPLIER*HASH_MULTIPLIER + b*HASH_MULTIPLIER + c);
        }
    };

    unordered_map<T, int, Hash> min_unstableness;
    unordered_map<T, string, Hash> min_molecule;

    int get_unstableness(const string &x) {
        int res = 0;
        int cur = 0;
        int len = x.length();
        REP(i, 0, len-1) {
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

    void dfs(int max_len, string cur) {
        if (cur.length() >= 2) {
            T abc = get_abc(cur);
            int unstableness = get_unstableness(cur);

            if (!min_unstableness.count(abc) || min_unstableness[abc] > unstableness) {
                min_unstableness[abc] = unstableness;
                min_molecule[abc] = cur;
            }
        }
        if ((int)cur.length() >= max_len) return;
        dfs(max_len, cur+"X");
        dfs(max_len, cur+"Y");
    }
public:
    void build(int max_len) {
        min_unstableness.clear();
        min_molecule.clear();
        dfs(max_len, "");
    }
    pair<int, string> get_unstableness(int a, int b, int c) {
        T ask = T(a, b, c);
        if (!min_unstableness.count(ask)) {
            return make_pair(-1, "");
        }
        return make_pair(min_unstableness[ask], min_molecule[ask]);
    }
};

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
        int csteps = 0;
        while (!q.empty()) {
            int f2, a, b, c, suf, b1;
            int key = q.front();
            q.pop();
            decompress(key, f2, a, b, c, suf, b1);

            int cur_dp = dp[compress(f2, a, b, c, suf, b1)];
            int b2 = suf>1 ? b1 : 1-b1;
            csteps++;

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
        fprintf(stderr, "csteps = %d\n", csteps);
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

class ConstructSolver {
    string gen_y_string(int cnt, int& block_yxy, int& block_y) {
        string res;
        // use Y first
        if (cnt<=2) {
            REP(i, 1, cnt) {
                if (block_y >= 1) {
                    res += "Y";
                    block_y--;
                } else {
                    assert(block_yxy >= 1);
                    res += "YXY";
                    block_yxy--;
                }
            }
        } else { // Y + YXY + Y + YXY...
            REP(i, 1, cnt) {
                if (i%2 == 0) {
                    assert(block_yxy >= 1); // TODO: ?
                    res += "YXY";
                    block_yxy--;
                } else if (block_y >= 1) {
                    res += "Y";
                    block_y--;
                } else {
                    assert(block_yxy >= 1);
                    res += "YXY";
                    block_yxy--;
                }
            }
        }
        return res;
    }

    string gen_yxy_end_string(int cnt, int& block_yxy, int& block_y) {
        assert(block_y < 0);
        assert(cnt == block_yxy + block_y);
        string res;

        // YXY + YXY => YXYXY
        REP(i, 1, abs(block_y) + 1) {
            if (i == 1) res += "YXY";
            else res += "XY";
        }
        block_yxy -= abs(block_y) + 1;
        block_y = 0;

        // remain YXY
        REP(i, 1, block_yxy) {
            res += "YXY";
        }
        block_yxy = 0;
        return res;
    }

    string gen_string(int cx, int block_yxy, int block_y, int block, bool rev) {
        string res;
        int div = cx / block;
        int rem = cx % block;
        int divy = (block_yxy + block_y) / block;
        int remy = (block_yxy + block_y) % block;

        REP(i, 0, block-1) {
            // add x block
            int cnt = (i<rem) ? div+1 : div;
            res += string(cnt, 'X');

            // add y block
            cnt = (i<remy) ? divy+1 : divy;
            if (i==block-1 && block_y<0) {
                res += gen_yxy_end_string(cnt, block_yxy, block_y);
            } else {
                res += gen_y_string(cnt, block_yxy, block_y);
            }
        }

        if (rev) {
            REP(i, 0, (int)res.length()-1) {
                if (res[i] == 'X') res[i] = 'Y';
                else res[i] = 'X';
            }
        }
        return res;
    }
public:
    pair<int, string> get_unstableness(int a, int b, int c) {
        if (c%2 == 1) {
            return make_pair(-1, "");
        }
        // XYXY...
        if (a==b && c==0) {
            string res;
            REP(i, 1, a) res += "XY";
            return make_pair(1, res);
        }
        // XXXX or YYYY
        if (c == 0) {
            if (a && b) return make_pair(-1, "");
            if (a) return make_pair(a, string(a, 'X'));
            else   return make_pair(b, string(b, 'Y'));
        }
        //     c/2 is odd
        //     #X = #Y =c/2
        // => extra "YYY" must exists
        // => contradition
        if (a==0 && b==0 && c%4==2) {
            return make_pair(-1, "");
        }

        int cx = a + c/2;
        int cy = b + c/2;
        bool revxy = false;
        if (cx < cy) {
            swap(cx, cy);
            swap(a, b);
            revxy = true;
        }

        // YXY + Y
        int block_yxy = b;
        int block_y   = cy - b*2;
        int block     = block_yxy + block_y;
        cx -= b;
        assert(cx >= block);
        assert(block >= 1); // c!=0

        if (cx / block <= 1) {
            int single = block - cx % block;
            block -= (single + 1) / 2;
        }
        if (block <= 0) {
            return make_pair(-1, "");
        }

#ifdef DEBUG
        printf("a, b, c = %d, %d, %d\n", a, b, c);
        printf("yxy, y, block = %d, %d, %d\n", block_yxy, block_y, block);
#endif
        return make_pair(
            (cx + block - 1) / block,
            gen_string(cx, block_yxy, block_y, block, revxy)
        );
    }
};

BruteforceSolver brute;
DPSolver dp;
ConstructSolver construct;
constexpr int MX_BRUTE = 25;
constexpr int MX_DP = 60;
constexpr int MX_CONSTRUCT = 200; // TODO

void test_brute_molecule() {
    fprintf(stderr, "\ntest_brute_molecule()...\n");
    REP(tot, 2, MX_BRUTE) REP(a, 0, MX_BRUTE) REP(b, 0, MX_BRUTE) {
        int c = tot - a - b;
        if (c < 0) break;

        int uns_brute;
        string molecule;
        tie(uns_brute, molecule) = brute.get_unstableness(a, b, c);
        if (uns_brute == -1) continue;

        T abc = get_abc(molecule);
        if (abc != make_tuple(a, b, c)) {
            int a2, b2, c2;
            tie(a2, b2, c2) = abc;
            printf("get_abc(%s) = (%d, %d, %d), but state = (%d, %d, %d)\n", molecule.c_str(), a2, b2, c2, a, b, c);
        }
    }
}

void test_dp_molecule() {
    fprintf(stderr, "\ntest_dp_molecule()...\n");
    REP(a, 0, MX_DP) REP(b, 0, MX_DP) REP(c, 0, MX_DP) {
        if (a+b+c < 2) continue;

        int uns_dp;
        string molecule;
        tie(uns_dp, molecule) = dp.get_unstableness(a, b, c);
        if (uns_dp == -1) continue;

        T abc = get_abc(molecule);
        if (abc != make_tuple(a, b, c)) {
            int a2, b2, c2;
            tie(a2, b2, c2) = abc;
            printf("get_abc(%s) = (%d, %d, %d), but state = (%d, %d, %d)\n", molecule.c_str(), a2, b2, c2, a, b, c);
        }
    }
}

void test_construct_molecule() {
    fprintf(stderr, "\ntest_construct_molecule()...\n");
    REP(a, 0, MX_CONSTRUCT) REP(b, 0, MX_CONSTRUCT) REP(c, 0, MX_CONSTRUCT) {
        if (a+b+c < 2) continue;

        int uns_construct;
        string molecule;
        tie(uns_construct, molecule) = construct.get_unstableness(a, b, c);
        if (uns_construct == -1) continue;

        T abc = get_abc(molecule);
        if (abc != make_tuple(a, b, c)) {
            int a2, b2, c2;
            tie(a2, b2, c2) = abc;
            printf("get_abc(%s) = (%d, %d, %d), but state = (%d, %d, %d)\n", molecule.c_str(), a2, b2, c2, a, b, c);
        }
    }
}

void test_brute_dp() {
    fprintf(stderr, "\ntest_brute_dp()...\n");
    REP(tot, 2, MX_BRUTE) REP(a, 0, MX_BRUTE) REP(b, 0, MX_BRUTE) {
        int c = tot - a - b;
        if (c < 0) break;

        int uns_brute;
        int uns_dp;
        string tmp;
        tie(uns_brute, tmp) = brute.get_unstableness(a, b, c);
        tie(uns_dp, tmp) = dp.get_unstableness(a, b, c);
        if (uns_brute != uns_dp) {
            printf("a,b,c = (%d, %d, %d); uns_brute=%d, uns_dp=%d\n", a, b, c, uns_brute, uns_dp);
        }
        if ((uns_brute==-1) != noans(a, b, c)) {
            printf("a,b,c = (%d, %d, %d); uns_brute=%d, uns_dp=%d, noans()=%d\n", a, b, c, uns_brute, uns_dp, noans(a, b, c));
        }
    }
}

void test_dp_construct() {
    fprintf(stderr, "\ntest_dp_construct()...\n");
    REP(a, 0, MX_DP) REP(b, 0, MX_DP) REP(c, 0, MX_DP) {
        if (a+b+c < 2) continue;

        int uns_dp;
        int uns_construct;
        string tmp;
        tie(uns_dp, tmp) = dp.get_unstableness(a, b, c);
        tie(uns_construct, tmp) = construct.get_unstableness(a, b, c);
        if (uns_dp != uns_construct) {
            printf("a,b,c = (%d, %d, %d); uns_dp=%d, uns_construct=%d\n", a, b, c, uns_dp, uns_construct);
        }
        if ((uns_dp==-1) != noans(a, b, c)) {
            printf("a,b,c = (%d, %d, %d); uns_dp=%d, uns_construct=%d, noans()=%d\n", a, b, c, uns_dp, uns_construct, noans(a, b, c));
        }
    }
}

int main()
{
    brute.build(MX_BRUTE);
    dp.build(MX_DP);

    test_brute_molecule();
    test_dp_molecule();
    test_construct_molecule();
    test_brute_dp();
    test_dp_construct();
    return 0;
}
