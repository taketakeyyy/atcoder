#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
// const long long INF = LONG_LONG_MAX - 1'001'001'001'001'001;
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

#include <atcoder/lazysegtree>
using SegS = long long;
using F = long long;
const SegS INF = 0; //
SegS op(SegS l, SegS r){ return std::min(l, r); }
SegS e(){ return INF; }
SegS mapping(F f, SegS x){ return f+x; }
F composition(F f, F g){ return f+g; }
F id(){ return 0; }

void solve() {
    ll N; cin >> N;
    string S; cin >> S;

    // vector zoro(10, vector(N+1, 0LL));
    // for(ll i=1; i<=N; i++) {
    //     for(ll n=0; n<=9; n++) {
    //         zoro[n][i] = zoro[n][i-1]*10 + n;
    //     }
    // }

    // 遅延セグメント木作成
    const ll MAX = 1e6;
    atcoder::lazy_segtree<SegS, op, e, F, mapping, composition, id> seg(MAX);
    for(ll i=0; i<N; i++) {
        ll n = S[i]-'0';
        if (n == 0) continue;
        ll keta = N-i;
        ll cnt = i+1;
        seg.apply(0, keta, n*cnt);
    }

    vector<ll> ans(MAX, 0LL);
    for(ll i=0; i<MAX-1; i++) {
        ll num = seg.get(i);
        ans[i] = num%10;
        seg.apply(i+1, i+1+1, num/10);
    }

    // 何桁まで埋めた？
    ll max_i;
    for(ll i=MAX; i>=0; i--) {
        if (ans[i] == 0) continue;
        max_i = i;
        break;
    }

    // 出力
    for(ll i=max_i; i>=0; i--) {
        cout << ans[i];
    }
    cout << endl;
}


int main() {
    solve();
    return 0;
}