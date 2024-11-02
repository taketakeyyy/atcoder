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

// (l,r)区間の数え上げ問題！
// 余事象を考えると逆に難しい。
// 普通に数え上げる方法を考える。
void solve() {
    ll N, M; cin >> N >> M;
    vector<pair<ll,ll>> RL(N);
    for(ll i=0; i<N; i++) {
        ll l, r; cin >> l >> r;
        RL[i] = {r,l};
    }
    sort(RL.begin(), RL.end());

    // 組(l,r)のrを固定して考える
    ll ans = 0;
    ll rl_idx = 0;
    ll mx_left = 0;
    for(ll r=1; r<=M; r++) {
        while(1) {
            if (rl_idx<N and RL[rl_idx].first == r) {
                chmax(mx_left, RL[rl_idx].second);
                rl_idx++;
                continue;
            }
            break;
        }

        // あり得るlの個数を数え上げる
        ans += r-mx_left;
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}