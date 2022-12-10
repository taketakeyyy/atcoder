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

ll N, K, D;

void f(vector<ll> &A, ll ii, ll depth, ll &total) {
    if (depth == K) {
        if (total%D == 0) {
            cout << total << endl;
            exit(0);
        }
    }

    for(ll i=ii; i<N; i++) {
        total += A[i];
        f(A, i+1, depth+1, total);
        total -= A[i];
    }
}

// TLE
void solve() {
    cin >> N >> K >> D;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];
    sort(A.begin(), A.end());
    reverse(A.begin(), A.end());

    ll total = 0;
    f(A, 0, 0, total);
    cout << -1 << endl;
}

void solve2() {
    cin >> N >> K >> D;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // dp[i][j][d] := i番目までにj個選んで、総和がd(%D)であるようなときの総和の最大値
    vector<vector<vector<ll>>> dp(N, vector<vector<ll>>(K+1, vector<ll>(D, -1)));
    for(ll i=0; i<N; i++) dp[i][0][0] = 0;
    dp[0][1][A[0]%D] = A[0];
    for(ll i=1; i<N; i++) {
        for(ll j=0; j<=min(i+1,K); j++) {
            for(ll d=0; d<D; d++) {
                // A[i]を選ばない場合
                dp[i][j][d] = max(dp[i][j][d], dp[i-1][j][d]);
                // A[i]を選ぶ場合
                if (j-1>=0 && dp[i-1][j-1][d]!=-1) {
                    dp[i][j][(d+A[i])%D] = max(dp[i][j][(d+A[i])%D], dp[i-1][j-1][d] + A[i]);
                }
            }
        }
    }

    cout << dp[N-1][K][0] << endl;
}


int main() {
    solve2();
    return 0;
}