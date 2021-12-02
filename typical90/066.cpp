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
    vector<ll> L(N), R(N);
    for (ll i=0; i<N; i++) {
        cin >> L[i] >> R[i];
    }

    // 期待値計算
    double expsum = 0.0;
    for (ll i=0; i<N; i++) {
        for (ll j=i+1; j<N; j++) {  // i < j となるように j を選ぶ
            // A[i] > A[j] を探す
            ll tentou = 0;  // 転倒数の数
            ll total = 0;   // 場合の数
            for (ll ai=L[i]; ai<=R[i]; ai++) {
                for (ll aj=L[j]; aj<=R[j]; aj++) {
                    if (ai > aj) tentou++;
                    total++;
                }
            }
            expsum += (double)tentou / total;
        }
    }

    // 答え出力
    printf("%.7lf\n", expsum);
}


int main() {
    solve();
    return 0;
}