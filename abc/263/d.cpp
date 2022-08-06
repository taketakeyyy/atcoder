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


void solve1() {
    ll N, L, R; cin >> N >> L >> R;
    vector<ll> A(N+1, 0);
    ll SUM = 0;
    vector<ll> rA(N+1, 0);  // 累積和
    for(ll i=1; i<N+1; i++) {
        cin >> A[i];
        SUM += A[i];
        rA[i] = rA[i-1] + A[i];
    }

    vector<ll> dpL(N+1, INF);  // dpL[i] := 1~iまでLに書き換えられるときの、配列全体の最小値
    dpL[0] = SUM;
    for(ll i=1; i<=N; i++) {
        dpL[i] = min(dpL[i-1], SUM - rA[i] + L*i);
    }

    vector<ll> dpR(N+1, INF);  // dpR[i] := i~NまでRに書き換えられるときの、配列全体の最小値
    dpR[N] = min(SUM, SUM-A[N]+R);
    for(ll i=N-1; i>=1; i--) {
        dpR[i] = min(dpR[i+1], SUM - (rA[N]-rA[i-1]) + R*(N-i+1));
    }

    // 答えを探す
    ll ans = SUM;
    for(ll i=0; i<=N; i++) {
        if (i == N) {
            ans = min(ans, dpL[i]);
        }
        else if (i == 0) {
            ans = min(ans, dpR[i+1]);
        }
        else {
            ans = min(ans, dpL[i] + dpR[i+1] - (rA[N]-rA[i]) - rA[i]);
        }
    }
    cout << ans << endl;
}

void solve2() {
    ll N, L, R; cin >> N >> L >> R;
    vector<ll> A(N+1, 0);
    ll SUM = 0;
    for(ll i=1; i<N+1; i++) {
        cin >> A[i];
        SUM += A[i];
    }

    // dpL[i] := 1~iまでLに書き換えられる場合の、1~Lまでの和の最小値
    vector<ll> dpL(N+1, 0);
    ll total = 0;
    for(ll i=1; i<=N; i++) {
        total += A[i];
        dpL[i] = min(total, L*i);
        if (i-1 >= 1) {
            dpL[i] = min(dpL[i], dpL[i-1]+A[i]);
        }
    }

    // dpR[i] := i~NまでRに書き換えられる場合の、i~Nまでの和の最小値
    vector<ll> dpR(N+2, 0);
    total = 0;
    for(ll i=N; i>=1; i--) {
        total += A[i];
        dpR[i] = min(total, R*(N-i+1));
        if (i+1 <= N) {
            dpR[i] = min(dpR[i], dpR[i+1]+A[i]);
        }
    }

    // 答えを探す
    ll ans = SUM;
    for(ll i=0; i<=N; i++) {
        ans = min(ans, dpL[i]+dpR[i+1]);
    }
    cout << ans << endl;
}


int main() {
    // solve1();
    solve2();
    return 0;
}