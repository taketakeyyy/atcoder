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
    ll N, X; cin >> N >> X;
    vector<ll> A(N+1), B(N+1);
    for(ll i=1; i<=N; i++) {
        cin >> A[i] >> B[i];
    }

    ll ans = INF;  // 答え
    ll total_t = 0;  // 累積時間
    ll mn = INF;  // 次にステージクリアにかかる最小時間
    for(ll i=1; i<=N; i++) {
        total_t += A[i] + B[i];
        mn = min(mn, B[i]);
        X--;

        if (X == 0) {
            ans = min(ans, total_t);
            cout << ans << endl;
            return;
        }

        // ここまでのクリアステージ状態で最小時間でクリアできるものでクリアする
        ans = min(ans, total_t+mn*X);
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}