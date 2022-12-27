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


// 点pのとりうる値の範囲は、x座標とy座標ともに[-5000, 5000]くらい。つまり幅10000。
void solve() {
    ll N, x, y; cin >> N >> x >> y;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // x座標の位置としてとりうる値の探索
    map<ll,bool> xpos;
    xpos[A[0]] = true;
    for(ll i=2; i<N; i+=2) { // O(N/2)
        map<ll,bool> newxpos;
        for(auto[x, val]: xpos) {  // 高々10000ステップ程度
            newxpos[x+A[i]] = true;
            newxpos[x-A[i]] = true;
        }
        xpos = newxpos;
    }

    // y座標の位置としてとりうる値の探索
    map<ll,bool> ypos;
    ypos[0] = true;
    for(ll i=1; i<N; i+=2) {
        map<ll,bool> newypos;
        for(auto[y, val]: ypos) {
            newypos[y+A[i]] = true;
            newypos[y-A[i]] = true;
        }
        ypos = newypos;
    }

    // 答え
    if (xpos.count(x) && ypos.count(y)) cout << "Yes" << endl;
    else cout << "No" << endl;
}


int main() {
    solve();
    return 0;
}