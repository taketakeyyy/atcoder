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
    ll N; cin >> N;

    // いもす法
    vector<ll> A(2*100000+1, 0);
    for(ll i=0; i<N; i++) {
        ll l, r; cin >> l >> r;
        A[l] += 1;
        A[r] -= 1;
    }
    for(ll i=0; i<2*100000; i++) {
        A[i+1] += A[i];
    }

    // 出力
    ll status = 0;
    ll ansl, ansr;
    for(ll i=0; i<2*100000+1; i++) {
        if (A[i] > 0 && status==0) {
            ansl = i;
            status = 1;
            continue;
        }
        if (A[i] <= 0 && status==1) {
            ansr = i;
            status = 0;
            cout << ansl << " " << ansr << endl;
            continue;
        }
    }
    if (status == 1) {
        cout << ansl << " " << 200000 << endl;
    }
}


int main() {
    solve();
    return 0;
}