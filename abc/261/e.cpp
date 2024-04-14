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

// 解説AC
// and, or, xor操作はbit毎に独立（他のbitから影響を受けない）
// g[N] = g[N] ○ ... ○ f[1] ○ f[0](X)
// g[0](X) = f[0](X)
// g[1](X) = f[1](f[0](X))
void solve1() {
    ll N, C; cin >> N >> C;
    vector<ll> T(N), A(N);
    for(ll i=0; i<N; i++) {
        cin >> T[i] >> A[i];
    }

    // 合成関数 g[i] = f[i] ○ f[i-1] ○ ... ○ f[1] を計算する
    vector<ll> ans(N);
    for(ll d=0; d<30; d++) { // bitごとに処理
        array<ll,2> g = {0, 1};
        ll crr = C>>d&1;
        for(ll i=0; i<N; i++) {
            array<ll,2> f;
            ll t = T[i], a = A[i];
            ll X = a>>d&1;
            if (t==1) { f={0&X, 1&X}; }
            if (t==2) { f={0|X, 1|X}; }
            if (t==3) { f={0^X, 1^X}; }
            g = {f[g[0]], f[g[1]]};
            crr = g[crr];
            ans[i] |= crr<<d;
        }
    }

    // 出力
    for(ll i=0; i<N; i++) {
        cout << ans[i] << endl;
    }
}

void solve3() {
    ll N, C; cin >> N >> C;
    vector<ll> d(2);
    d[1] = ~0;
    for(ll i=0; i<N; i++) {
        ll t, a; cin >> t >> a;
        for(ll j=0; j<2; j++) {
            if (t == 1) d[j] &= a;
            if (t == 2) d[j] |= a;
            if (t == 3) d[j] ^= a;
        }
        C = (C&d[1]) | (~C&d[0]);
        cout << C << endl;
    }
}

int main() {
    solve1();
    // solve2();
    // solve3();
    return 0;
}