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
    ll N, Q; cin >> N >> Q;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    ll ptr = 0;  // 先頭のインデックスを指し示すポインタ（ポインタではない）
    for(ll q=0; q<Q; q++) {
        ll t, x, y;
        cin >> t >> x >> y;
        if (t == 1) {
            // 入れ替えは普通にやる
            x--; y--;
            swap(A[(ptr+x)%N], A[(ptr+y)%N]);
        }
        else if (t == 2) {
            // 先頭を指し示すポインタを左にずらすイメージ
            ptr = (ptr-1+N) % N;
        }
        else {
            // 出力
            x--;
            cout << A[(ptr+x)%N] << endl;
        }
    }
}


int main() {
    solve();
    return 0;
}