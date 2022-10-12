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
    ll N; cin >> N;
    vector<ll> A(N), B(N), C(N);
    for(ll i=0; i<N; i++) cin >> A[i];
    for(ll i=0; i<N; i++) cin >> B[i];
    for(ll i=0; i<N; i++) cin >> C[i];
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());
    sort(C.begin(), C.end());

    // 中部のパーツを決めたら、使える上部と下部を二分探索する
    ll ans = 0;
    for(ll bi=0; bi<N; bi++) {
        ll ai = lower_bound(A.begin(), A.end(), B[bi]) - A.begin();
        ll ci = upper_bound(C.begin(), C.end(), B[bi]) - C.begin();
        ans += ai*(N-ci);
    }

    // 出力
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}