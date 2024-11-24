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


void solve() {
    ll N, M; cin >> N >> M;
    vector<ll> X(M), A(M);
    for(ll i=0; i<M; i++) cin >> X[i];
    for(ll i=0; i<M; i++) cin >> A[i];
    vector<pair<ll,ll>> masu(M);
    for(ll i=0; i<M; i++) masu[i] = {X[i], A[i]};
    sort(masu.begin(), masu.end());

    // マス1に石が置いてなかったら、もうだめ
    if (masu[0].first != 1) {
        cout << -1 << endl;
        return;
    }

    // 1+2+...+nを計算
    auto f = [&](ll a, ll l, ll n) -> ll {
        return ((a+l)*n)/2;
    };

    // マスNから決めていく
    ll ans = 0;
    ll r = N;
    for(ll i=M-1; i>=0; i--) {
        ll l = masu[i].first;
        ll dist = r - l;
        if (dist+1 == masu[i].second) {
            ans += f(1, dist, dist);
            r = masu[i].first-1;
            continue;
        }
        else if (dist+1 > masu[i].second){
            // 石が足りない
            ans += f(dist-masu[i].second+1,dist,masu[i].second);
            r -= masu[i].second;
        }
        else {
            // 石があまる
            cout << -1 << endl;
            return;
        }
    }
    if (r != 0) {
        cout << -1 << endl;
        return;
    }
    cout << ans << endl;

}


int main() {
    solve();
    return 0;
}