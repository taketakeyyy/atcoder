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
using S = long long;
// 最大用
S op1(S a, S b) { return max(a, b); }
S e1() { return -1; }
// 最小用
S op2(S a, S b) { return min(a, b); }
S e2() { return INF; }

void solve() {
    ll N, K; cin >> N >> K;
    vector<pair<ll,ll>> P(N);
    for(ll i=0; i<N; i++) {
        ll p; cin >> p;
        P[i] = {p, i+1};
    }
    sort(P.begin(), P.end());

    vector<ll> A(N);
    for(ll i=0; i<N; i++) {
        A[i] = P[i].second;
    }

    // セグメントツリー作成
    atcoder::segtree<S, op1, e1> segMax(A);
    atcoder::segtree<S, op2, e2> segMin(A);
    ll ans = INF;
    for(ll r=K; r<=N; r++) {
        ll l = r-K;
        ll mn = segMin.prod(l, r);
        ll mx = segMax.prod(l, r);
        chmin(ans, mx-mn);
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}