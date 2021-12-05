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
    ll N, K; cin >> N >> K;
    vector<ll> A(N), B(N);
    for(ll i=0; i<N; i++) {
        cin >> A[i] >> B[i];
    }
    ll H = *max_element(A.begin(), A.end());
    ll W = *max_element(B.begin(), B.end());

    vector<vector<ll>> S(H+1, vector<ll>(W+1, 0));  // 二次元累積和
    for(ll i=0; i<N; i++) {
        S[A[i]][B[i]] += 1;
    }

    // h方向の累積和
    for(ll h=1; h<=H; h++) {
        for(ll w=0; w<=W; w++) {
            S[h][w] += S[h-1][w];
        }
    }
    // w方向の累積和
    for(ll w=1; w<=W; w++) {
        for(ll h=0; h<=H; h++) {
            S[h][w] += S[h][w-1];
        }
    }

    // 答えを探す
    ll ans = 1;
    for(ll h=0; h<=H; h++) {
        for (ll w=0; w<=W; w++) {
            // (K+1)x(K+1)の正方形領域の累積和を走査したい
            ll h1 = max(h-(K+1), 0LL);
            ll w1 = max(w-(K+1), 0LL);
            ll tmp = S[h][w] - S[h][w1] - S[h1][w] + S[h1][w1];
            ans = max(ans, tmp);
        }
    }

    // 答えを出力
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}