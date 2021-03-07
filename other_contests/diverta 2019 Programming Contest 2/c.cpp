#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) (a+(b-1))/b
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve() {
    // (1) どれか1個は必ず負になる。それ以外は自由にプラスマイナスをつけて良い。
    // (2) どれか1個は必ず正になる。それ以外は自由にプラスマイナスをつけて良い。
    // 上記のどちらかになる
    ll N; cin >> N;
    vector<ll> plus, minus;
    rep(i,N) {
        ll a; cin >> a;
        if (a > 0) {
            plus.push_back(a);
        }
        else {
            minus.push_back(a);
        }
    }
    sort(plus.begin(), plus.end());
    sort(minus.begin(), minus.end());

    ll ans;
    vector<pair<ll,ll>> ops;  // 操作列
    if ((ll)minus.size()==N) {
        // 一番絶対値が小さいやつを正にして、それ以外はマイナスをつける
        ll x, y;
        x = minus[N-1];
        for (int i=N-2; i>=0; i--) {
            y = minus[i];
            ops.push_back(make_pair(x, y));
            x = x - y;
        }
        ans = x;
    }
    else if ((ll)plus.size()==N) {
        // 一番絶対値が小さいやつを負にして、それ以外はプラスを付ける
        ll x, y;
        x = plus[0];
        for (ll i=1; i<N-1; i++) {
            y = plus[i];
            ops.push_back(make_pair(x,y));
            x = x - y;
        }
        y = x;
        x = plus[N-1];
        ops.push_back(make_pair(x,y));
        ans = x - y;
    }
    else {
        // minusのやつにマイナスを、plusのやつはプラスにできる
        ll x, y;
        x = minus[0];
        for (ll i=0; i<(ll)plus.size()-1; i++) {
            y = plus[i];
            ops.push_back(make_pair(x,y));
            x = x - y;
        }
        y = x;
        x = plus[plus.size()-1];
        ops.push_back(make_pair(x,y));
        x = x - y;
        for (ll i=1; i<(ll)minus.size(); i++) {
            y = minus[i];
            ops.push_back(make_pair(x,y));
            x = x - y;
        }
        ans = x;
    }

    // 出力
    cout << ans << endl;
    for (ll i=0; i<(ll)ops.size(); i++) {
        cout << ops[i].first << " " << ops[i].second << endl;
    }
}


int main() {
    solve();
    return 0;
}