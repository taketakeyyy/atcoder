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
    ll N, K; cin >> N >> K;
    vector<ll> A(K);
    set<ll> Aset;  // ライト持ってる集団
    for(ll k=0; k<K; k++) {
        cin >> A[k];
        A[k]--;
        Aset.insert(A[k]);
    }
    vector<ll> X(N);
    vector<ll> Y(N);
    for(ll i=0; i<N; i++) {
        ll x, y; cin >> x >> y;
        X[i] = x;
        Y[i] = y;
    }

    vector<double> D(N, (double)INF);  // iの人がライトで照らされる最小距離
    for(ll k=0; k<K; k++) {
        ll ak = A[k];
        for(ll i=0; i<N; i++) {
            // ライト持ってるやつは照らさなくていい
            if (Aset.count(i)) continue;

            // ak と iの人との距離
            double d = sqrt((X[ak]-X[i])*(X[ak]-X[i]) + (Y[ak]-Y[i])*(Y[ak]-Y[i]));
            D[i] = min(D[i], d);
        }
    }

    // Dの中の最大距離が答え
    double ans = (double)0;
    for(ll i=0; i<N; i++) {
        if (D[i] == (double)INF) continue;
        ans = max(ans, D[i]);
    }

    printf("%.5lf\n", ans);
}


int main() {
    solve();
    return 0;
}