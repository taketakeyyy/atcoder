#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/b)
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    string S; cin >> S;

    // 1の条件
    {
        ll x = -1, y = -1;
        for(ll i=0; i<8; i++) {
            if (S[i] == 'B') {
                if (x == -1) x = i;
                else y = i;
            }
        }
        if (x%2 == y%2) {
            cout << "No" << endl;
            return;
        }
    }
    // 2の条件
    {
        ll x=-1, y=-1;
        ll z=-1;
        for(ll i=0; i<8; i++) {
            if (S[i] == 'R') {
                if (x == -1) x = i;
                else y = i;
            }
            else if (S[i] == 'K') {
                z = i;
            }
        }

        if (!(x<z && z<y)) {
            cout << "No" << endl;
            return;
        }
    }
    cout << "Yes" << endl;
}


int main() {
    solve();
    return 0;
}