#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) (a+(b-1))/b
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve() {
    ll N; cin >> N;
    vector<ll> A(N);
    vector<ll> B(N);
    for(int i=0; i<N; i++) {
        cin >> A[i] >> B[i];
    }
    // N=奇数の場合を考える
    // Xの中央値を最小値は？=>すべてAを選んだときの中央値=>Lとする
    // Xの中央値を最大値は？=>すべてBを選んだときの中央値=>Rとする
    // では、[L, R]の範囲の整数はすべて作れるのか？？？
    // 絵を描くとなるっぽいが、解説動画が詳しい
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    ll ans;
    if (N%2==1) {
        // 奇数の時は1ずつ作れる
        ll L = A[N/2];
        ll R = B[N/2];
        ans = R-L+1;
    }
    else {
        // 偶数の時は0.5ずつ作れる
        // ans = (R-L)/0.5+1
        // 浮動小数点数を扱いたくないので、RとLに2をかけた整数2Rと2Lで扱いたい
        // ans = 2R-2L+1
        //
        ll L = (A[N/2-1]+A[N/2]);
        ll R = (B[N/2-1]+B[N/2]);
        ans = R-L+1;
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}