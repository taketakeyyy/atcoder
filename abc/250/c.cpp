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
    map<ll,ll> mp;  // ボールのインデックスを保持
    for(ll i=0; i<N; i++) {
        A[i] = i+1;
        mp[i+1] = i;
    }

    for(ll q=0; q<Q; q++) {
        ll x; cin >> x;
        ll idx = mp[x];

        if (idx != N-1) {
            // 右端じゃないなら
            mp[A[idx]] = idx+1;
            mp[A[idx+1]] = idx;
            swap(A[idx], A[idx+1]);
        }
        else {
            mp[A[idx]] = idx-1;
            mp[A[idx-1]] = idx;
            swap(A[idx], A[idx-1]);
        }
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