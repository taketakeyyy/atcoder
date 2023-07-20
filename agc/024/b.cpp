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
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


// 解説AC
void solve() {
    ll N; cin >> N;
    vector<ll> P(N);

    // mp[p] := pはPのi番目
    map<ll,ll> mp;
    for(ll i=0; i<N; i++) {
        cin >> P[i];
        mp[P[i]] = i;
    }

    // 最長増加部分列の長さを求める
    vector<ll> A(N+1);
    ll longest = 0;
    ll len = 0;
    ll pre_i = -1;
    for(ll i=1; i<=N; i++) {
        if (mp[i] > pre_i) {
            len++;
            longest = max(longest, len);
        }
        else {
            len = 1;
            longest = max(longest, len);
        }
        pre_i = mp[i];
    }

    // 答え
    cout << N - longest << endl;
}


// インラインDP解法
void solve2() {
    ll N; cin >> N;
    vector<ll> P(N);

    // mp[p] := pはPのi番目
    map<ll,ll> mp;
    for(ll i=0; i<N; i++) {
        cin >> P[i];
        mp[P[i]] = i;
    }

    // dp[a] := (左からi番目まで見て)、増加部分列Bに最後に追加した要素がaのときの、Bの長さの最大値
    vector<ll> dp(N+1, 0);
    dp[0] = 0; // Bが空のとき
    for(ll i=0; i<N; i++) {
        dp[P[i]] = max(dp[P[i]], max(dp[P[i]-1]+1, 1LL));
    }

    // 答え
    ll ans = 0;
    for(ll i=0; i<N; i++) {
        ans = max(ans, dp[P[i]]);
    }
    cout << N-ans << endl;
}

int main() {
    // solve();
    solve2();
    return 0;
}