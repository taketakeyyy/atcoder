#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll N, K; cin >> N >> K;
    vector<ll> A(N), B(N);
    for(ll i=0; i<N; i++) cin >> A[i];
    for(ll i=0; i<N; i++) cin >> B[i];
    // ソートしてN^2マス計算してもOK
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    // N^2マス計算の値がx以下の値となる個数が、K個以上か？
    auto f = [&](ll x) {
        ll cnt = 0;
        for(ll i=0; i<N; i++) { // 各行に対して調べる
            ll col = x/A[i];
            ll idx = upper_bound(B.begin(), B.end(), col) - B.begin();
            cnt += idx;
        }
        return cnt>=K;
    };

    // 二分探索する
    ll l=1, r=1e18+1;
    while(r-l != 1) {
        ll mid = (l+r)/2;
        if (f(mid)) r = mid;
        else l = mid;
    }
    if (f(l)) cout << l << endl;
    else cout << r << endl;
}


int main() {
    solve();
    return 0;
}