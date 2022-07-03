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
    const ll r = 1e9;  // 半径r
    const ll rr = 1e8;  // 少し小さい半径rr
    vector<ll> A(10+1);  // 各100人以下。合計はたかだか1000人
    for(ll i=1; i<=10; i++) {
        cin >> A[i];
    }

    vector<pair<ll,ll>> berry(N);  // いちごの座標
    for(ll i=0; i<N; i++) {
        ll x, y; cin >> x >> y;
        berry[i] = {x, y};
    }

    // 適当にK等分(100等分)してみる
    cout << K << endl;
    double dtheta = (double)2*M_PI/K;
    for(ll k=0; k<K; k++) {
        double theta = dtheta*k;
        ll x = rr * sin(theta);
        ll y = rr * cos(theta);
        cout << "0 0 " << x << " " << y << '\n';
    }
}


int main() {
    solve();
    return 0;
}