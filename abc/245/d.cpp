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
    vector<ll> A(N+1), B(M+1), C(N+M+1);
    for(ll i=0; i<N+1; i++) cin >> A[i];
    for(ll i=0; i<N+M+1; i++) cin >> C[i];

    ll bi = M;
    for(ll ci=N+M; ci>=N; ci--) {
        B[bi] = C[ci]/A[N];

        // C[]の値を減算する
        for(ll ai=N; ai>=0; ai--) {
            C[ci-(N-ai)] -= B[bi]*A[ai];
        }
        bi--;
    }

    // 出力
    for(ll i=0; i<M+1; i++) {
        cout << B[i] << " ";
    }
    cout << endl;
}


int main() {
    solve();
    return 0;
}