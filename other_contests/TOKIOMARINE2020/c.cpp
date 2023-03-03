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
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


// A[i]の値がaのとき、「iから距離a個隣りまで照らす」
// シミュレーションすると、いずれAの値はすべてNに収束する
// 収束するまでの回数は、Nよりずっと小さい
void solve() {
    ll N, K; cin >> N >> K;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // シミュレーションする
    ll cnt = 0; // シミュレーション回数
    while(1) {
        // 終了条件
        bool is_allN = true;
        for(ll i=0; i<N; i++) {
            if (A[i] != N) is_allN = false;
        }
        if (is_allN) break;
        if (cnt == K) break;

        // いもす法
        vector<ll> imos(N+1);
        for(ll i=0; i<N; i++) {
            ll x = A[i];
            ll l = max(0LL, i-x);
            ll r = min(N-1, i+x);
            imos[l] += 1;
            imos[r+1] -= 1;
        }
        // 累積和をとる
        A[0] = imos[0];
        for(ll i=1; i<N; i++) {
            imos[i] += imos[i-1];
            A[i] = imos[i];
        }
        cnt++;
    }

    // 出力
    for(ll i=0; i<N; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
}


int main() {
    solve();
    return 0;
}