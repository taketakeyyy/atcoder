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
    ll H, W; cin >> H >> W;
    vector<string> S(H), T(H);
    for(ll h=0; h<H; h++) {
        cin >> S[h];
    }
    for(ll h=0; h<H; h++) {
        cin >> T[h];
    }

    map<string,ll> mapS;
    for(ll w=0; w<W; w++) {
        string s = "";
        for(ll h=0; h<H; h++) {
            s += {S[h][w]};
        }
        mapS[s]++;
    }

    for(ll w=0; w<W; w++) {
        string s = "";
        for(ll h=0; h<H; h++) {
            s += {T[h][w]};
        }
        mapS[s]--;
    }

    bool is_ok = true;
    for(auto[s, v]: mapS) {
        if (v==0) continue;
        is_ok = false;
        break;
    }

    if (is_ok) cout << "Yes" << endl;
    else cout << "No" << endl;

}


int main() {
    solve();
    return 0;
}