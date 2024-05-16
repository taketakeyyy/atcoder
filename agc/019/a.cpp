#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll Q, H, S, D; cin >> Q >> H >> S >> D;
    ll N; cin >> N;
    // 整数リットルにしたいのでサイズをすべて4倍にする
    // これで1,2,4,8リットルサイズのボトルになる
    N *= 4;
    // 8リットルあたりの価格でソート
    vector<tuple<ll,ll,ll>> V; // (8リットルあたりの価格, サイズ, 価格)
    V.push_back({8*Q, 1, Q});
    V.push_back({4*H, 2, H});
    V.push_back({2*S, 4, S});
    V.push_back({1*D, 8, D});
    sort(V.begin(), V.end());

    // 8リットルあたりの価格が安い順に貪欲に買っていく
    ll ans = 0;
    for(auto[normalize_price, size, price]: V) {
        ans += price*(N/size);
        N %= size;
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}