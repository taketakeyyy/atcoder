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
    // 入力
    ll N, Q; cin >> N >> Q;
    vector<ll> X(Q), Y(Q), Z(Q), W(Q);
    for(ll q=0; q<Q; q++) {
        cin >> X[q] >> Y[q] >> Z[q] >> W[q];
        X[q]--; Y[q]--; Z[q]--;
    }

    // 全探索
    ll ans = 1LL;
    for(ll d=0; d<60; d++) {  // 各桁dごとに考える
        vector<ll> w(Q);  // この桁のwの値
        for(ll q=0; q<Q; q++) {
            w[q] = (W[q]>>d)&1;
        }

        ll ways = 0;
        // この桁の数列Aの値をbit全探索
        for(ll bit=0; bit<(1<<N); bit++) {
            vector<ll> A(N, 0);  // この桁の数列Aの値
            for(ll n=0; n<N; n++) {
                A[n] = (bit>>n)&1;
            }

            bool flag = true;
            for(ll q=0; q<Q; q++) {
                if ((A[X[q]] | A[Y[q]] | A[Z[q]]) != w[q]) flag = false;
            }

            if (flag) ways++;
        }

        ans *= ways;
        ans %= MOD;
    }

    // 出力
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}