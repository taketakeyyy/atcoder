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
    ll H, W, K; cin >> H >> W >> K;
    vector<string> grid(H);
    for(ll i=0; i<H; i++) {
        cin >> grid[i];
    }

    ll ans = INF;
    // 横方向の走査。しゃくとり法
    if (K <= W) {
        for(ll i=0; i<H; i++) {
            map<char,ll> mp;
            for(ll j=0; j<K; j++) {
                mp[grid[i][j]]++;
            }
            if (mp['x'] == 0) ans = min(ans, mp['.']);

            for(ll j=1; j<=W-K; j++) {
                mp[grid[i][j-1]]--;
                mp[grid[i][j+K-1]]++;

                if (mp['x'] == 0) ans = min(ans, mp['.']);
            }
        }
    }

    // 縦方向の走査。しゃくとり法
    if (K <= H) {
        for(ll j=0; j<W; j++) {
            map<char, ll> mp;
            for(ll i=0; i<K; i++) {
                mp[grid[i][j]]++;
            }
            if (mp['x'] == 0) ans = min(ans, mp['.']);

            for(ll i=1; i<=H-K; i++) {
                mp[grid[i-1][j]]--;
                mp[grid[i+K-1][j]]++;

                if (mp['x'] == 0) ans = min(ans, mp['.']);
            }
        }
    }

    // 答え
    if (ans == INF) cout << -1 << endl;
    else cout << ans << endl;
}


int main() {
    solve();
    return 0;
}