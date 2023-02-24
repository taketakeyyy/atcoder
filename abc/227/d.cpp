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
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll N, K; cin >> N >> K;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // 二分探索用関数。x個のプロジェクトを作れるか？
    auto f = [&](ll x) -> bool {
        ll total = 0;
        for(ll i=0; i<N; i++) total += min(A[i], x);
        return total >= K*x;
    };

    // プロジェクトをx個作れるとして二分探索
    ll l=0;
    ll r=intceil(N*1e12, K); // N個の部署が全部1e12人いる場合、N*1e12/K の切り上げ？
    while(r-l > 1) {
        ll mid = (l+r)/2;
        if (f(mid)) l = mid;
        else r = mid;
    }
    if (f(r)) cout << r << endl;
    else cout << l << endl;
}


int main() {
    solve();
    return 0;
}