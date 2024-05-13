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


// なるべく大きな金額の硬貨から貪欲に使えばよい（小さい硬貨は融通が利くので）
void solve() {
    ll A, B, C, D, E, F; cin >> A >> B >> C >> D >> E >> F;
    ll N; cin >> N;
    vector<ll> X(N);
    for(ll i=0; i<N; i++) {
        cin >> X[i];
    }

    // money円の硬貨がrest枚あるときに、x円を支払う
    auto f = [&](ll money, ll &rest, ll &x) {
        ll cnt = x / money; // 枚数
        if (cnt > rest) {
            x -= rest*money;
            rest = 0;
        }
        else {
            x -= cnt*money;
            rest -= cnt;
        }
    };

    // 大きな金額の硬貨から貪欲に使う
    for(ll i=0; i<N; i++) {
        ll x = X[i];
        f(500, F, x);
        f(100, E, x);
        f(50, D, x);
        f(10, C, x);
        f(5, B, x);
        f(1, A, x);
        if (x == 0) continue;
        cout << "No" << endl;
        return;
    }
    cout << "Yes" << endl;
}


int main() {
    solve();
    return 0;
}