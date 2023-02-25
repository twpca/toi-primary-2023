// O(a+b+c), non-optimal solution
// Expect: PC
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M
using namespace std;

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
bool noans(int a,int b, int c) {
    if (c%2 == 1) return true;
    if (a==0 && b==0 && c%4==2) return true;
    if (c==0 && a!=b && a!=0 && b!=0) return true;
    if (c==2 && a==b) return true;
    return false;
}
void out(string x) {
    if (x == "") {
        puts("-1");
    } else {
        printf("%d\n", get_unstableness(x));
        printf("%s\n", x.c_str());
    }
}
int main()
{
    int a, b, c;
    while (~scanf("%d %d %d", &a, &b, &c)) {
        if (noans(a, b, c)) {
            out("");
            continue;
        }
        if (c == 0) {
            if (a == b) {
                string tmp = "";
                REP(i,1,a) tmp += "XY";
                out(tmp);
            } else if (a) {
                out(string(a, 'X'));
            } else {
                out(string(b, 'Y'));
            }
            continue;
        }

        int cx = a + c/2;
        int cy = b + c/2;
        bool rev = false;
        if (cx < cy) {
            swap(a, b);
            swap(cx, cy);
            rev = true;
        }

        string suffix = "";
        if (b) {
            REP(i,1,b) {
                suffix += "YX";
            }
            suffix += "Y";
            cy -= b+1;
            cx -= b;
        }

        string ans = "";
        int blocks = -1;
        if (cy == 0) {
            blocks = 1;
        } else {
            blocks = (cy / 2) + (cy % 2);
        }
        int divx = cx / blocks;
        int remx = cx % blocks;
        REP(i,1,blocks) {
            if (i <= remx) ans += string(divx+1, 'X');
            else ans += string(divx, 'X');

            if (cy >= 1) {
                ans += "Y";
                cy--;
            }
            if (i == blocks) {
                ans += suffix;
            }
            if (cy >= 1) {
                ans += "Y";
                cy--;
            }
        }
        if (rev) {
            REP(i,0,(int)ans.length()-1) {
                if (ans[i] == 'X') ans[i] = 'Y';
                else ans[i] = 'X';
            }
        }
        out(ans);
    }
    return 0;
}
