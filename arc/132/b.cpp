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

ll op1(vector<ll> &P, ll &N) {
    // 4 5 1 2 3 パターン
    // (1) 操作2を繰り返す
    // (2) 反転して、操作2を繰り返して、反転する
    ll ans = INF;
    for(ll i=1; i<N; i++) {
        if (P[i-1] < P[i]) continue;
        if (P[i-1] > P[i]) {
            ans = min(i, N-i+2);
            break;
        }
    }
    return ans;
}

ll op2(vector<ll> &P, ll &N) {
    // 2 1 5 4 3 パターン
    // (1) 操作2してから反転
    // (2) 反転してから操作2
    ll ans = INF;
    for(ll i=1; i<N; i++) {
        if (P[i-1] > P[i]) continue;
        if (P[i-1] < P[i]) {
            ans = min(i+1, N-i+1);
            break;
        }
    }
    return ans;
}

void solve() {
    ll N; cin >> N;
    vector<ll> P(N);
    // 1~nの順列
    for(ll i=0; i<N; i++) {
        cin >> P[i];
    }

    ll ans;
    if (P[0]==1 && P[N-1]==N) {
        ans = 0;
    }
    else if (P[0]==N && P[N-1]==1) {
        ans = 1;
    }
    else if (P[0] < P[1]) {
        ans = op1(P, N);
    }
    else if (P[0] > P[1]) {
        ans = op2(P, N);
    }

    // 出力
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}