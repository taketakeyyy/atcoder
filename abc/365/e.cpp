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

    // 累積xorを求める
    vector<ll> ruiA(N+1);
    for(ll i=0; i<N; i++) ruiA[i+1] = ruiA[i] ^ A[i];

    // 各桁について独立に、答えを足し合わせる
    ll ans = 0;
    for(ll d=0; d<30; d++) { //d桁目
        ll one = 0; // d桁目が1のものの個数
        for(ll i=0; i<=N; i++) {
            if (ruiA[i]>>d&1) one++;
        }
        ll zero = (N+1)-one; //d桁目が0のものの個数
        ans += one*zero*(1LL<<d);
    }

    // 足しすぎたものを引く
    for(ll i=1; i<=N; i++) ans -= ruiA[i]^ruiA[i-1];
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}