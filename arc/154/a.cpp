#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 998244353
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
    ll N; cin >> N;
    string A, B; cin >> A >> B;

    // Aに小さい数字を集める
    ll p10 = 1;
    ll totalA = 0;
    ll totalB = 0;
    for(ll i=N-1; i>=0; i--) {
        ll a = A[i] - '0';
        ll b = B[i] - '0';
        if (a > b) swap(a,b);
        totalA += (a*p10) % MOD;
        totalB += (b*p10) % MOD;
        totalA %= MOD;
        totalB %= MOD;
        p10 *= 10; p10 %= MOD;
    }
    ll ans = (totalA * totalB) % MOD;
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}