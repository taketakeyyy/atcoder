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
    ll N; cin >> N;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // ピラミッドの左半分の作れる高さを求める
    vector<ll> left(N);
    left[0] = 1;
    for(ll i=1; i<N; i++) left[i] = min(left[i-1]+1, A[i]);

    // ピラミッドの右半分の作れる高さを求める
    vector<ll> right(N);
    right[0] = 1;
    reverse(A.begin(), A.end());
    for(ll i=1; i<N; i++) right[i] = min(right[i-1]+1, A[i]);
    reverse(right.begin(), right.end());

    // 作れるピラミッドの高さは、ピラミッドの左半分と右半分のmin
    ll ans = 1;
    for(ll i=0; i<N; i++) ans = max(ans, min(left[i], right[i]));
    cout << ans << endl;
}

int main() {
    solve();
    return 0;
}