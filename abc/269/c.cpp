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

/*
100000000000000000001000000000000000000010000000000000000000
10000000000000000000
1000000000000000000000000000000000000000
100000000000000000000000000000000000000000000000000000000000
*/
void solve() {
    ll N; cin >> N;

    vector<ll> binks;  // 2^kの値
    for(ll d=0; d<60; d++) {
        if (N>>d&1) {
            ll x = 1LL<<d;  // 1LLにしないと駄目
            binks.push_back(x);
        }
    }

    // 2^kの和をbit全探索
    vector<ll> ans;
    ll bsz = binks.size();  // 最大15
    for(ll bit=0; bit<(1<<bsz); bit++) {
        ll x = 0;
        for(ll d=0; d<bsz; d++) {
            if (bit>>d&1) {
                x += binks[d];
            }
        }
        ans.push_back(x);
    }

    // 出力
    for(ll a: ans) {
        cout << a << endl;
    }
}


int main() {
    solve();
    return 0;
}