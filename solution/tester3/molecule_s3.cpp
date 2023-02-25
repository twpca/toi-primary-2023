// O(a+b+c), special case
// Expect: subtask3 only
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M
using namespace std;

int main()
{
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    if (c%2 == 1) {
        puts("-1");
        return 0;
    }

    int cx = a + c/2;
    int cy = b + c/2;
    bool rev = false;
    if (cx < cy) {
        swap(a, b);
        swap(cx, cy);
        rev = true;
    }

    string ans = "";
    int div, rem;
    if (cy == 0) {
        div = cx;
        rem = 0;
        ans = string(cx, 'X');
    } else {
        div = cx / cy;
        rem = cx % cy;
        REP(i,0,cy-1) {
           int cnt = (i<rem) ? div+1 : div;
            ans += string(cnt, 'X');
            ans += "Y";
        }
    }

    if (rev) {
        REP(i,0,(int)ans.length()-1) {
            if (ans[i] == 'X') ans[i] = 'Y';
            else ans[i] = 'X';
        }
    }
    printf("%d\n", div + (rem?1:0));
    printf("%s\n", ans.c_str());
    return 0;
}
