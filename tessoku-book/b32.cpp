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
    ll N, K; cin >> N >> K;
    vector<ll> A(K);
    for(ll k=0; k<K; k++) {
        cin >> A[k];
    }

    // dp[i] := 残りの石がi個のときに自分が手番のとき、勝ち確定（true）か負け確定（false）か
    vector<bool> dp(N+1, false);
    for(ll i=0; i<=N; i++) {
        for(ll k=0; k<K; k++) {
            if (i-A[k]>=0 && !dp[i-A[k]]) dp[i] = true;
        }
    }

    // 出力
    if (dp[N]) cout << "First" << endl;
    else cout << "Second" << endl;
}


int main() {
    solve();
    return 0;
}