#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 998244353
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

template<typename T>
T mod_pow(T a, T n, T m) {
    /** a^{n} mod m の計算を、繰り返し二乗法で求める
     *  計算量：O(log n)
     **/
    if (n==0) return 1;
    T res = mod_pow(a*a%m, n/2, m);
    if (n&1) res = res * a % m;
    return res;
}

void solve() {
    ll N, M, K; cin >> N >> M >> K;

    if (K == 0) {
        ll ans = mod_pow<ll>(M, N, MOD);
        cout << ans << endl;
        return;
    }

    vector<vector<ll>> dp(N, vector<ll>(M+1, 0));  // dp[i][a] := i番目のAiの値がaのときの場合の数
    for(ll a=1; a<=M; a++) {
        for(ll k=K; k<=M; k++) {
            if (a+k <= M) {
                dp[0][a] += 1;
                dp[1][a+k] += 1;
            }
            if (a-k >= 1) {
                dp[0][a] += 1;
                dp[1][a-k] += 1;
            }
        }
    }
    for(ll i=2; i<N; i++) {
        // 累積和
        vector<ll> ruiseki(M+1, 0);
        for(ll a=1; a<=M; a++) {
            ruiseki[a] = ruiseki[a-1] + dp[i-1][a];
            // ruiseki[a] %= MOD;  しないほうがいい
        }

        // DPうめる
        for(ll a=1; a<=M; a++) {
            if (0 <= a+K-1 && a+K-1 <= M) {
                dp[i][a] += ruiseki[M] - ruiseki[a+K-1];
                dp[i][a] %= MOD;
            }
            if (0 <= a-K) {
                dp[i][a] += ruiseki[a-K];
                dp[i][a] %= MOD;
            }
        }
    }

    // 答え
    ll ans = 0;
    for(ll a=1; a<=M; a++) {
        ans += dp[N-1][a];
        ans %= MOD;
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}