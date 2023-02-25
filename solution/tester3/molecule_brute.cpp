// O(2^(a+b+c))
// Expect: subtask1
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
BruteforceSolver brute;

int main()
{
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    brute.build(a+b+c);

    int a1;
    string a2;
    tie(a1, a2) = brute.get_unstableness(a, b, c);
    if (a1 == -1) {
        puts("-1");
    } else {
        printf("%d\n%s\n", a1, a2.c_str());
    }
    return 0;
}
