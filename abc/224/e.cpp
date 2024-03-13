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
    ll H, W, N; cin >> H >> W >> N;
    vector<ll> R(N), C(N), A(N);

    map<ll, vector<ll>> mp; // mp[a] := 値aを持つインデックスのリスト
    for(ll i=0; i<N; i++) {
        cin >> R[i] >> C[i] >> A[i];
        R[i]--; C[i]--;
        mp[A[i]].push_back(i);
    }

    vector<ll> rmax(H, -1); //rmax[i] := i行のマスで最も大きい移動回数
    vector<ll> cmax(W, -1); //cmax[i] := i列のマスで最も大きい移動回数
    vector<ll> dp(N, 0); // dp[i] := コマがマスiに置かれているときの、移動回数の最大値
    for(auto it = mp.rbegin(); it!=mp.rend(); it++) { // aの降順にdpを埋めていく
        // dp更新
        for(auto i: it->second) {
            dp[i] = max(rmax[R[i]]+1, cmax[C[i]]+1);
        }
        // rmax,cmaxの更新
        for(auto i: it->second) {
            rmax[R[i]] = max(rmax[R[i]], dp[i]);
            cmax[C[i]] = max(cmax[C[i]], dp[i]);
        }
    }

    // 出力
    for(ll i=0; i<N; i++) cout << dp[i] << endl;
}


int main() {
    solve();
    return 0;
}