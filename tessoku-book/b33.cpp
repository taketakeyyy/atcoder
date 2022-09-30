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
    ll N, H ,W; cin >> N >> H >> W;

    // ニム和 = 0 なら、後手必勝
    ll nim_sum = 0;
    for(ll i=0; i<N; i++) {
        ll a, b; cin >> a >> b;
        a--; b--;
        nim_sum ^= a;
        nim_sum ^= b;
    }

    // 出力
    if (nim_sum == 0) cout << "Second" << endl;
    else cout << "First" << endl;
}


int main() {
    solve();
    return 0;
}