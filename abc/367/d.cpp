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
    ll N, M; cin >> N >> M;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];
    vector<ll> A2 = A; // 2周分結合
    A2.insert(A2.end(), A.begin(), A.end());
    vector<ll> S2(2*N+1); // A2の累積和
    for(ll i=0; i<2*N; i++) {
        S2[i+1] = S2[i] + A2[i];
        S2[i+1] %= M;
    }

    // 最初のN-1個の分布をとる
    ll ans = 0;
    map<ll,ll> mp;
    for(ll i=0; i<=N-1; i++) {
        mp[S2[i]]++;
    }
    ans += mp[S2[0]]-1;

    // 尺取法
    for(ll i=1; i<=N-1; i++) {
        mp[S2[i-1]]--;
        mp[S2[i+(N-1)]]++;
        ans += mp[S2[i]]-1;
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}