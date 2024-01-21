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


// 解説AC
// 桁DP
void solve() {
    ll N; cin >> N;
    N++; // 「N未満の良い整数は全部で何通り？」を考えたほうがラクなので

    // Nの各桁を配列にしておく
    vector<ll> digit;
    while(N) {
        digit.push_back(N%10);
        N /= 10;
    }
    reverse(digit.begin(), digit.end());
    ll M = digit.size();

    // dp[i][j][s][r] := 上位からi桁目が、N未満フラグがjで、桁和がsで、kで割ったあまりがrのときの、場合の数
    // vector dp(16, vector<vector<vector<ll>>>(2, vector<vector<ll>>(130, vector<ll>(130))));
    vector dp(16, vector(2, vector(130, vector(130, 0LL))));
    ll ans = 0;
    for(ll k=1; k<=126; k++) {
        for(ll i=0; i<=M; i++) {
            for(ll j=0; j<2; j++) {
                for(ll s=0; s<=k; s++) {
                    for(ll r=0; r<k; r++) dp[i][j][s][r] = 0;
                }
            }
        }
        dp[0][0][0][0] = 1;


        for(ll i=0; i<M; i++) {
            for(ll j=0; j<2; j++) {
                for(ll s=0; s<=k; s++) {
                    for(ll r=0; r<k; r++) {
                        for(ll d=0; d<10; d++) {
                            ll ni = i+1;
                            ll nj = j;
                            ll ns = s+d;
                            ll nr = (r*10+d)%k;
                            if (ns > k) continue;
                            if (j==0) {
                                if (digit[i] < d) continue;
                                if (digit[i] > d) nj = 1;
                            }
                            dp[ni][nj][ns][nr] += dp[i][j][s][r];
                        }
                    }
                }
            }
        }
        ans += dp[M][1][k][0];
    }
    cout << ans << endl;
}

// 解説AC
// 自分なりの桁DP
void solve2() {
    ll N; cin >> N;

    // Nの各桁を配列にしておく
    vector<ll> digit;
    while(N) {
        digit.push_back(N%10);
        N /= 10;
    }
    reverse(digit.begin(), digit.end());
    ll M = digit.size();

    // dp[i][j][s][r] := Nのi桁目まで見て、N未満フラグがjで、桁和がsで、kで割ったあまりがrのときの、場合の数
    // 9*16桁 = 144 -> 桁和は144になる可能性がある
    ll ans = 0;
    for(ll k=1; k<=144; k++) { // kで割る
        vector dp(M, vector(2, vector(145, vector(145, 0LL))));
        { // 0桁目の初期状態
            ll n = digit[0];
            dp[0][0][n][n%k] = 1;
            for(ll num=0; num<n; num++) {
                dp[0][1][num][num%k] = 1;
            }
        }

        // 1桁目移行の遷移
        for(ll i=1; i<M; i++) {
            ll n = digit[i];

            // N未満フラグ0から、N未満フラグ0への遷移
            for(ll s=0; s<145; s++) {
                ll ns = s+n;
                if (ns >= 145) break;
                for(ll r=0; r<145; r++) {
                    ll nr = (r*10+n)%k;
                    if (nr >= 145) continue;
                    dp[i][0][ns][nr] += dp[i-1][0][s][r];
                }
            }
            // N未満フラグ0から、N未満フラグ1への遷移
            for(ll num=0; num<n; num++) {
                for(ll s=0; s<145; s++) {
                    ll ns = s+num;
                    if (ns >= 145) break;
                    for(ll r=0; r<145; r++) {
                        ll nr = (r*10+num)%k;
                        if (nr >= 145) continue;
                        dp[i][1][ns][nr] += dp[i-1][0][s][r];
                    }
                }
            }
            // N未満フラグ1から、N未満フラグ1への遷移
            for(ll num=0; num<=9; num++) {
                for(ll s=0; s<145; s++) {
                    ll ns = s+num;
                    if (ns >= 145) break;
                    for(ll r=0; r<145; r++) {
                        ll nr = (r*10+num)%k;
                        if (nr >= 145) continue;
                        dp[i][1][ns][nr] += dp[i-1][1][s][r];
                    }
                }
            }
        }

        // 答えを数え上げる（桁和がkで、kで割ったあまりが0のものを数え上げる）
        ans += dp[M-1][0][k][0];
        ans += dp[M-1][1][k][0];
    }
    cout << ans << endl;
}

int main() {
    // solve();
    solve2();
    return 0;
}