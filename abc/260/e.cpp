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


void solve() {
    ll N, M; cin >> N >> M;
    vector<ll> A(N), B(N);
    map<ll, vector<ll>> LR;  // LR[i] := A[i]のときのB[i]
    ll r = 0;  // 右端
    ll bmin = M+1;  // Bの最小値
    for(ll i=0; i<N; i++) {
        cin >> A[i] >> B[i];
        LR[A[i]].push_back(B[i]);
        r = max(r, A[i]);
        bmin = min(bmin, B[i]);
    }

    // いもす法でf(k)を求める
    vector<ll> f(M+2, 0);
    f[r] = 1; f[M+1] = -1;

    // 左端をlと固定したとき、右端rの最小値を求める
    for(ll l=2; l<=bmin; l++) {
        // 右端更新
        for(auto b: LR[l-1]) {
            r = max(r, b);
        }
        // いもす法加算処理
        f[r-l+1] += 1;
        f[M-l+1+1] -= 1;
    }

    // いもす法の累積和
    for(ll i=1; i<=M+1; i++) {
        f[i] += f[i-1];
    }

    // 出力
    for(ll i=1; i<=M; i++) {
        cout << f[i] << " ";
    }
    cout << endl;
}


int main() {
    solve();
    return 0;
}