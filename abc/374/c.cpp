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


void solve() {
    ll N; cin >> N;
    vector<ll> K(N);
    for(ll i=0; i<N; i++) cin >> K[i];

    ll ans = INF;
    for(ll bit=0; bit<(1<<N); bit++) {
        ll A = 0;
        ll B = 0;
        for(ll d=0; d<N; d++) {
            if (bit>>d&1) A += K[d];
            else B += K[d];
        }

        chmin(ans, max(A,B));
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}