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
    ll N; cin >> N;
    const ll M = ll(1e6)+10;
    vector<ll> cnt(M+1); // cnt[m] := 値mの頻度分布
    for(ll i=0; i<N; i++) {
        ll a; cin >> a;
        cnt[a]++;
    }

    // 分布の累積和を作る
    vector<ll> ruiCnt(M+1); // 分布の累積和
    for(ll i=1; i<=M; i++) ruiCnt[i] = ruiCnt[i-1] + cnt[i-1];

    // 区間[l,r)の和
    auto sum = [&](ll l, ll r) {
        r = min(M,r);
        return ruiCnt[r]-ruiCnt[l];
    };

    ll ans = 0;
    for(ll y=1; y<=M; y++) {
        ll total = 0;
        for(ll x=1; x*y<=M; x++) {
            ll l = y*x;
            ll r = y*(x+1);
            total += sum(l,r)*x;
        }
        total -= cnt[y];
        ans += total*cnt[y];
        ans += cnt[y]*(ll)(cnt[y]-1LL)/2LL; // 自分と同じ値の組み合わせ分 組み合わせC(cnt[y],2)
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}