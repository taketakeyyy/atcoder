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

#include <atcoder/segtree>
using S = map<ll,ll>; // 値:個数
S op(S mp1, S mp2) { // 区間取得の演算をどのように行うか
    map<ll,ll> res;
    for(auto[key, val]: mp1) res[key] += val;
    for(auto[key, val]: mp2) res[key] += val;
    // サイズが2になるまで、小さいやつを消していく
    while(res.size() != 2) {
        auto it = res.begin();
        res.erase(it);
    }
    return res;
}
S e() { // 単位元
    map<ll,ll> res;
    res[-1] = 0;
    res[-2] = 0;
    return res;
}

void solve() {
    ll N, Q; cin >> N >> Q;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // セグメントツリー作成
    vector<map<ll,ll>> B(N);
    for(ll i=0; i<N; i++) {
        map<ll,ll> mp;
        mp[0] = 0; // 便宜上
        mp[A[i]] = 1;
        B[i] = mp;
    }
    atcoder::segtree<S, op, e> seg(B);

    // クエリ処理
    for(ll q=0; q<Q; q++) {
        ll query; cin >> query;
        if (query == 1) {
            // タイプ1：A[p]の値をxに変更する
            ll p, x; cin >> p >> x;
            p--;
            map<ll,ll> mp;
            mp[0] = 0;
            mp[x] = 1;
            seg.set(p, mp);
        }
        else {
            // タイプ2：Aの区間[l,r]において2番目に大きい値の個数を出力する
            ll l, r; cin >> l >> r;
            l--; r--;
            auto mp = seg.prod(l,r+1);
            ll ans = (*mp.begin()).second;
            cout << ans << endl;
        }
    }
}


int main() {
    solve();
    return 0;
}