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

// void solve2() {
//     cpp_int N, M, K; cin >> N >> M >> K;
//     if (N > M) swap(N,M);

//     cpp_int lm = lcm(N,M);
//     cpp_int cntN = lm/N - 1;
//     cpp_int cntM = lm/M - 1;
//     cpp_int cntLap = cntN + cntM; // 1周期あたりの個数
//     cpp_int lap = (K-1)/cntLap; // 何周期目か
//     cpp_int restK = K - lap*cntLap; // 残りのK

//     cpp_int now = lap*lm;

//     cpp_int n = 0;
//     cpp_int m = 0;
//     while(1) {
//         if (restK == 0) break;
//         if (n <= m) {
//             n += N; restK--;
//         }
//         else {
//             m += M; restK--;
//         }
//     }
//     if (n >= m) {
//         cout << now+n << endl;
//     }
//     else {
//         cout << now+m << endl;
//     }
// }

int main() {
    solve();
    // solve2();
    return 0;
}