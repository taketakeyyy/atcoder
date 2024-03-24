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
    ll N, K; cin >> N >> K;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // 1以上K以下の和を求める
    ll ans = ((1+K)*K)/2;

    // 1以上K以下のうち、Aの中に現れたものを引く
    unordered_set<ll> used;
    for(ll a: A) {
        if (a > K) continue;
        if (used.count(a)) continue;
        used.insert(a);
        ans -= a;
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}