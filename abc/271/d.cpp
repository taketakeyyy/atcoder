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
    ll N, S; cin >> N >> S;
    vector<ll> A(N+1), B(N+1);
    for(ll i=1; i<=N; i++) {
        cin >> A[i] >> B[i];
    }

    // dp[i][j][x] := i枚目のカードまでを見て、表(j=0)か裏(j=1)を選んだときの、累積和がxになるかどうか
    vector dp(N+1, vector<vector<bool>>(2, vector<bool>(S+1, false)));
    dp[0][0][0] = true;
    dp[0][1][0] = true;
    for(ll i=1; i<=N; i++) {
        for(ll x=0; x<=S; x++) {
            if (x-A[i] >= 0) {
                dp[i][0][x] = dp[i][0][x] | dp[i-1][0][x-A[i]];
                dp[i][0][x] = dp[i][0][x] | dp[i-1][1][x-A[i]];
            }
            if (x-B[i] >= 0) {
                dp[i][1][x] = dp[i][1][x] | dp[i-1][0][x-B[i]];
                dp[i][1][x] = dp[i][1][x] | dp[i-1][1][x-B[i]];
            }
        }
    }

    // 出力
    string ans = "";
    if (dp[N][0][S] || dp[N][1][S]) {
        ll x = S;
        for(ll i=N; i>=1; i--) {
            if (dp[i][0][x]) {
                x -= A[i];
                ans = "H" + ans;
                continue;
            }
            else {
                x -= B[i];
                ans = "T" + ans;
                continue;
            }
        }
        cout << "Yes" << endl;
        cout << ans << endl;
    }
    else {
        cout << "No" << endl;
    }
}


int main() {
    solve();
    return 0;
}