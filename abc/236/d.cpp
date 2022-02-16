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

ll N;
map<pair<ll,ll>,ll> Amap;
ll ans = -INF;
vector<bool> is_used;

void calc(set<ll> &rest, set<pair<ll,ll>> &pairs) {
    bool is_end = true;
    for (ll i=1; i<=2*N; i++) {
        if (!is_used[i]) {
            is_end = false;
            break;
        }
    }

    if (is_end) {
        // 楽しさ計算
        ll happy = 0;
        for (auto pair: pairs) {
            happy ^= Amap[pair];
        }
        ans = max(ans, happy);
        return;
    }

    // 一番小さいやつは？
    ll mn = INF;
    for (auto i: rest) {
        if (is_used[i]) continue;
        mn = min(mn, i);
    }
    is_used[mn] = true;

    // 残りから、全探索
    for (auto j: rest) {
        if (is_used[j]) continue;
        is_used[j] = true;
        pairs.insert({mn,j});
        calc(rest, pairs);
        is_used[j] = false;
        pairs.erase({mn,j});
    }

    is_used[mn] = false;
}

void solve() {
    cin >> N;
    for(ll i=1; i<=2*N-1; i++) {
        for(ll j=i+1; j<=2*N; j++) {
            ll a; cin >> a;
            Amap[{i,j}] = a;
        }
    }
    is_used.resize(2*N+1, false);

    set<ll> rest;
    for (ll i=1; i<=2*N; i++) {
        rest.insert(i);
    }
    set<pair<ll,ll>> pairs;
    calc(rest, pairs);

    // 出力
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}