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
    vector<ll> A(N), B(N);
    // 座標圧縮いもす法（イベントソート）
    map<ll,ll> event;
    for(ll i=0; i<N; i++) {
        cin >> A[i] >> B[i];
        event[A[i]] += 1;
        event[A[i]+B[i]] -= 1;
    }

    vector<ll> ans(N+1, 0);
    ll k = 0;
    ll preday = 0;
    for(auto[day, val]: event) {
        ans[k] += (day-preday);
        k += val;
        preday = day;
    }

    for(ll i=1; i<=N; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
}


int main() {
    solve();
    return 0;
}