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
// #include<boost/multiprecision/cpp_int.hpp>
// using namespace boost::multiprecision;

void solve() {
    ll N, M, K; cin >> N >> M >> K;
    if (N > M) swap(N,M);

    ll lm = lcm(N,M);
    ll cntN = lm/N - 1;
    ll cntM = lm/M - 1;
    ll cntLap = cntN + cntM; // 1周期あたりの個数
    ll lap = (K-1)/cntLap; // 何周期目か
    ll restK = K - lap*cntLap; // 残りのK

    ll now = lap*lm;

    // 残りはシミュレーション
    ll n = 0;
    ll m = M;
    while(1) {
        if (restK == 0) break;
        ll nn = n + N;
        if (nn > m) {
            // m, nn の順
            restK--;
            if (restK == 0) {
                cout << now+m << endl;
                return;
            }
            restK--;
            if (restK == 0) {
                cout << now+nn << endl;
                return;
            }
            n = nn;
            m += M;
        }
        else {
            restK--;
            if (restK == 0) {
                cout << now+nn << endl;
                return;
            }
            n = nn;
        }
    }
}

// 解説AC　二分探索
void solve2() {
    ll N, M, K; cin >> N >> M >> K;
    if (N > M) swap(N,M);

    const ll LCM = lcm(N,M);

    // x以下の正整数のうち、NとMのうちちょうど一方で割り切れるものの個数がK個以上か？
    auto f = [&](ll x) {
        ll cntN = x/N; // Nで割り切れるものの個数
        ll cntM = x/M; // Mで割り切れるものの個数
        ll cntLCM = x/LCM; // NとMで割り切れるものの個数
        ll cnt = cntN + cntM - 2*cntLCM; // NとMのどちらか一方でのみ割り切れるものの個数
        return cnt >= K;
    };

    ll l=1, r=2e18;
    while(r-l != 1) {
        ll mid = (l+r)/2;
        if (f(mid)) r = mid;
        else l = mid;
    }
    if (f(l)) cout << l << endl;
    else cout << r << endl;
}

int main() {
    // solve();
    solve2();
    return 0;
}