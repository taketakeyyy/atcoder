#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
const long long INF = LONG_LONG_MAX - 1'001'001'001'001'001;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };
//ordered_set
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// 初項a, 末項l, 項数n のときの等差数列の和
ll tousa1(const ll &a, const ll &l, const ll &n) { return ((a+l)*n)/2; }
// 初項a, 公差d, 項数n のときの等差数列の和
ll tousa2(const ll &a, const ll &d, const ll &n) { return ((2*a+(n-1)*d)*n)/2; }


void solve() {
    ll N; cin >> N;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    const ll D = 25; // 2^25 ≒ 3e7
    vector<ll> zerocnt(D); // zerocnt[d] := 「少なくとも末尾d桁が0」の個数
    for(ll d=0; d<D; d++) {
        ll mod = 1<<d;
        vector<ll> sum(mod); // sum[a] := a(mod mod)の和
        vector<ll> cnt(mod); // cnt[a] := a(mod mod)の個数
        ll now = 0;
        for(ll i=0; i<N; i++) {
            sum[A[i]%mod] += A[i];
            cnt[A[i]%mod]++;
            ll b = (mod-A[i]%mod)%mod;
            now += sum[b];
            now += cnt[b]*A[i];
        }
        zerocnt[d] = now;
    }

    // 「ぴったり末尾d桁が0」の個数を作る
    for(ll d=0; d<D-1; d++) {
        zerocnt[d] -= zerocnt[d+1];
    }

    ll ans = 0;
    for(ll d=0; d<D; d++) ans += zerocnt[d]>>d;
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}