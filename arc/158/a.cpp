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


// 差は 2 と 4 ずつ埋まっていくので、
// 好きな要素にそれぞれ +0 +2 +4 すると考えてよい
// さらに発展して、-2 0 +2 すると考えて良い
// (さらに発展して、全体を1/2して -1 0 +1 すると考えて良い)
void solve() {
    ll T; cin >> T;
    for(ll t=0; t<T; t++) {
        vector<ll> x(3);
        cin >> x[0] >> x[1] >> x[2];
        sort(x.begin(), x.end());

        x[1] -= x[0];
        x[2] -= x[0];
        x[0] -= x[0];

        // 各要素が2の倍数じゃないなら -1
        bool is_ng = false;
        for(ll i=0; i<3; i++) {
            if (x[i]%2 != 0) {
                is_ng = true;
                break;
            }
        }
        if (is_ng) {
            cout << -1 << endl;
            continue;
        }

        // 和が3の倍数じゃないなら -1
        if ((x[1]+x[2])%3 != 0) {
            cout << -1 << endl;
            continue;
        }

        // 最終的に3つの数を s にすると考える
        ll s = (x[1]+x[2])/3;

        // 正の変化量/2 が答え
        ll d = 0;
        d += (s >= 0 ? s : 0);
        d += (s-x[1] >= 0 ? s-x[1] : 0);
        d += (s-x[2] >= 0 ? s-x[2] : 0);
        ll ans = d/2;
        // ll ans = d;
        cout << ans << endl;
    }
}


int main() {
    solve();
    return 0;
}