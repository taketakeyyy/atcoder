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
    string T; cin >> T;
    ll N; cin >> N;
    vector<vector<string>> S(N);
    for(ll i=0; i<N; i++) {
        ll A; cin >> A;
        for(ll a=0; a<A; a++) {
            string s; cin >> s;
            S[i].push_back(s);
        }
    }

    // dp[i][t] := i袋目まで見て、Tのt文字目まで作れるときの、最小金額
    ll TN = T.size();
    vector<ll> dp(TN+1, INF);
    dp[0] = 0;
    for(ll i=0; i<N; i++) {
        vector olddp = dp;

        for(ll t=0; t<TN; t++) { // Tのt文字目
            if (olddp[t] == INF) continue;

            for(ll j=0; j<(ll)S[i].size(); j++) { // S[i]のj番目の文字列
                string s = S[i][j];

                // Tのt文字目から、sが一致するか？
                bool is_ok = true;
                for(ll k=0; k<s.size(); k++) {
                    if (s[k]==T[t+k]) continue;
                    is_ok = false;
                    break;
                }
                if (is_ok) {
                    ll sn = s.size();
                    chmin(dp[t+sn], olddp[t]+1);
                }
            }
        }
    }
    if (dp[TN] == INF) cout << -1 << endl;
    else cout << dp[TN] << endl;
}


int main() {
    solve();
    return 0;
}