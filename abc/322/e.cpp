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


void solve() {
    ll N, K, P; cin >> N >> K >> P;
    vector<ll> C(N);
    vector<vector<ll>> A(N, vector<ll>(5, 0));
    for(ll i=0; i<N; i++) {
        cin >> C[i];
        for(ll j=0; j<K; j++) {
            cin >> A[i][j];
        }
    }

    // dp[i][p0][p1][p2][p3][p4] := i個目まで見て、k0のパラメータがp0、k1のパラメータがp1、...のときの、コストの総和の最小値
    vector dp(6, vector<vector<vector<vector<ll>>>>(6, vector<vector<vector<ll>>>(6, vector<vector<ll>>(6, vector<ll>(6, INF)))));
    dp[0][0][0][0][0] = 0;
    for(ll i=1; i<=N; i++) {
        auto olddp = dp;
        // 採用する場合
        ll c = C[i-1];
        for(ll p0=0; p0<=5; p0++) {
            ll a0 = A[i-1][0];

            for(ll p1=0; p1<=5; p1++) {
                ll a1 = A[i-1][1];

                for(ll p2=0; p2<=5; p2++) {
                    ll a2 = A[i-1][2];

                    for(ll p3=0; p3<=5; p3++) {
                        ll a3 = A[i-1][3];

                        for(ll p4=0; p4<=5; p4++) {
                            ll a4 = A[i-1][4];

                            dp[min(5LL,p0+a0)][min(5LL,p1+a1)][min(5LL,p2+a2)][min(5LL,p3+a3)][min(5LL,p4+a4)] = min(dp[min(5LL,p0+a0)][min(5LL,p1+a1)][min(5LL,p2+a2)][min(5LL,p3+a3)][min(5LL,p4+a4)], olddp[p0][p1][p2][p3][p4]+c);
                        }
                    }
                }
            }
        }
    }

    // 答え
    ll ans = INF;
    if (K == 5) {
        for(ll p0=P; p0<=5; p0++) {
            for(ll p1=P; p1<=5; p1++) {
                for(ll p2=P; p2<=5; p2++) {
                    for(ll p3=P; p3<=5; p3++) {
                        for(ll p4=P; p4<=5; p4++) {
                            ans = min(ans, dp[p0][p1][p2][p3][p4]);
                        }
                    }
                }
            }
        }
    }
    if (K == 4) {
        for(ll p0=P; p0<=5; p0++) {
            for(ll p1=P; p1<=5; p1++) {
                for(ll p2=P; p2<=5; p2++) {
                    for(ll p3=P; p3<=5; p3++) {
                        ans = min(ans, dp[p0][p1][p2][p3][0]);
                    }
                }
            }
        }
    }
    if (K == 3) {
        for(ll p0=P; p0<=5; p0++) {
            for(ll p1=P; p1<=5; p1++) {
                for(ll p2=P; p2<=5; p2++) {
                    ans = min(ans, dp[p0][p1][p2][0][0]);
                }
            }
        }
    }
    if (K == 2) {
        for(ll p0=P; p0<=5; p0++) {
            for(ll p1=P; p1<=5; p1++) {
                ans = min(ans, dp[p0][p1][0][0][0]);
            }
        }
    }
    if (K == 1) {
        for(ll p0=P; p0<=5; p0++) {
            ans = min(ans, dp[p0][0][0][0][0]);
        }
    }
    if (ans != INF) {
        cout << ans << endl;
    }
    else {
        cout << -1 << endl;
    }
}


int main() {
    solve();
    return 0;
}