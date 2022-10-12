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
    ll D; cin >> D;
    ll N; cin >> N;
    ll M; cin >> M;
    vector<ll> shop_pos(N+1);
    shop_pos[0] = 0; shop_pos[N] = D; // 0 と D も含めると便利
    for(ll i=1; i<=N-1; i++) {
        cin >> shop_pos[i];
    }
    sort(shop_pos.begin(), shop_pos.end());

    // どの店舗が配達すべきか二分探索
    ll ans = 0;
    for(ll m=0; m<M; m++) {
        ll k; cin >> k;
        ll i = upper_bound(shop_pos.begin(), shop_pos.end(), k) - shop_pos.begin();
        ans += min(abs(shop_pos[i]-k), abs(shop_pos[i-1]-k));
    }

    // 出力
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}