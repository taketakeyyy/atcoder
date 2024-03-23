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
    ll N, T, M; cin >> N >> T >> M;
    vector<ll> A(M), B(M);
    for(ll i=0; i<M; i++) {
        cin >> A[i] >> B[i];
        A[i]--; B[i]--;
    }

    // n!を計算
    auto kaijo = [&](ll n) {
        ll res = 1;
        for(ll i=1; i<=n; i++) res *= i;
        return res;
    };

    // チームstは仲の悪い人間が含まれていない、平和なチームか？
    auto is_team_ok = [&](set<ll> &st) {
        for(ll i=0; i<M; i++) {
            if (st.count(A[i]) and st.count(B[i])) {
                return false;
            }
        }
        return true;
    };

    // O(T 3^N (N+M))
    // dp[t][s] := t番目のチームを決めるとき、すでに使った選手の状態がsのときの、場合の数
    vector<ll> dp(1<<N, 0);
    dp[0] = 1;
    for(ll t=0; t<T; t++) {
        vector<ll> newdp(1<<N, 0);

        // 今回の状態s
        for(ll s=1; s<1<<N; s++) {
            set<ll> team;
            for(ll d=0; d<N; d++) {
                if (s>>d&1) {
                    team.insert(d);
                }
            }

            if (!is_team_ok(team)) continue;

            // sを反転させたfs
            ll fs = ~s; fs &= (1<<N)-1;
            for(ll t=fs;; t=(t-1)&fs) { // tはfsの部分集合
                // tからs|tへ遷移する
                newdp[s|t] += dp[t];
                if (t==0) break;
            }
        }
        swap(newdp, dp);
    }

    // 答え
    cout << dp[(1<<N)-1]/kaijo(T) << endl;
}


int main() {
    solve();
    return 0;
}