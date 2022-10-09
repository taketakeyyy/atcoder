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


// スイッチの個数Nが最大10と小さいので、スイッチの状態の組み合わせをbit全探索できる
void solve() {
    ll N, M; cin >> N >> M;
    vector<vector<ll>> denkyu(M);
    for(ll i=0; i<M; i++) {
        ll K; cin >> K;
        for(ll j=0; j<K; j++) {
            ll s; cin >> s; s--;
            denkyu[i].push_back(s);
        }
    }
    vector<ll> P(M);
    for(ll i=0; i<M; i++) {
        ll p; cin >> p;
        P[i] = p;
    }

    // スイッチの状態をbit全探索する。
    // スイッチの各状態について、全ての電球が点灯するかチェックする
    ll ans = 0;
    for(ll bit=0; bit<(1<<N); bit++) {
        bool is_ok = true;  // すべて点灯しているか？
        for(ll i=0; i<M; i++) {
            // 各電球iについて、点灯するかチェック
            ll on_num = 0;
            for(auto s: denkyu[i]) {
                if (bit>>s&1) on_num++;
            }
            if (on_num%2 == P[i]) continue;
            is_ok = false;
        }

        if (is_ok) ans++;
    }

    // 出力
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}