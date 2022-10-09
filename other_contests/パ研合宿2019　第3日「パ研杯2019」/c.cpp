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


void solve() {
    ll N, M; cin >> N >> M;
    vector<vector<ll>> A(N, vector<ll>(M));
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<M; j++) cin >> A[i][j];
    }

    // t1, t2 を全探索
    ll ans = 0;
    for(ll t1=0; t1<M; t1++) {
        for(ll t2=t1+1; t2<M; t2++) {
            ll total = 0;
            for(ll i=0; i<N; i++) total += max(A[i][t1], A[i][t2]);
            ans = max(ans, total);
        }
    }

    // 出力
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}