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
    ll N, A, B; cin >> N >> A >> B;
    // dp[i] := 残りの石の数がi個のときに手番が回ってきたとき、勝ち確か(true)負け確か(false)
    vector<ll> dp(N+1, false);

    for(ll i=0; i<=N; i++) {
        if (i-A>=0 && !dp[i-A]) dp[i] = true;
        else if (i-B>=0 && !dp[i-B]) dp[i] = true;
        else dp[i] = false;
    }

    // 出力
    if (dp[N]) cout << "First" << endl;
    else cout << "Second" << endl;
}


int main() {
    solve();
    return 0;
}