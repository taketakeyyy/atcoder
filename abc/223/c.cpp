#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
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


void solve() {
    ll N; cin >> N;
    vector<double> A(N);
    vector<double> B(N);
    for(ll i=0; i<N; i++) {
        cin >> A[i] >> B[i];
    }

    // まず燃え尽きる時間を計測する
    // 1本ずつ燃やした場合の、1/2の時間で燃え尽きる
    double T = 0;
    for(ll i=0; i<N; i++) {
        T += A[i]/B[i];
    }
    T = T/2;

    // 左から燃やしてt秒後を計測する
    double rest = T;  // 残り時間
    double ans = 0;
    for(ll i=0; i<N; i++) {
        double t = A[i]/B[i];
        if (rest-t > 0) {
            rest -= t;
            ans += A[i];
            continue;
        }
        else {
            ans += B[i]*rest;
            printf("%.6lf\n", ans);
            return;
        }
    }
}


int main() {
    solve();
    return 0;
}