// O(a+b+c)
// Expect: AC
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M
using namespace std;
using T = tuple<int,int,int>;

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
                    assert(block_yxy >= 1);
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

        return make_pair(
            (cx + block - 1) / block,
            gen_string(cx, block_yxy, block_y, block, revxy)
        );
    }
};
ConstructSolver construct;

int main()
{
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);

    int a1;
    string a2;
    tie(a1, a2) = construct.get_unstableness(a, b, c);
    if (a1 == -1) {
        puts("-1");
    } else {
        printf("%d\n%s\n", a1, a2.c_str());
    }
    return 0;
}
