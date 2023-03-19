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


// イベントソート
void solve() {
    ll L, N1, N2; cin >> L >> N1 >> N2;
    vector<tuple<ll,ll,ll>> block1; // (始点,終点,値)のブロック
    {
        ll idx = 1;
        for(ll i=0; i<N1; i++) {
            ll v, l; cin >> v >> l;
            ll s = idx;
            ll t = s + l - 1;
            block1.push_back({s,t,v});
            idx = t+1;
        }
    }
    vector<tuple<ll,ll,ll>> block2;
    {
        ll idx = 1;
        for(ll i=0; i<N2; i++) {
            ll v, l; cin >> v >> l;
            ll s = idx;
            ll t = s + l - 1;
            block2.push_back({s,t,v});
            idx = t+1;
        }
    }

    // ブロックが重なるところで、値が同じところの個数を数える
    ll ans = 0;
    ll i1 = 0, i2 = 0;
    while(1) {
        if (i1==N1 || i2==N2) break;

        auto[s1, t1, v1] = block1[i1];
        auto[s2, t2, v2] = block2[i2];
        if (s1 > t2) { i2++; continue; }
        if (s2 > t1) { i1++; continue; }

        if (v1 == v2) ans += min(t1,t2) - max(s1,s2) + 1;

        if (t1 > t2) i2++;
        else i1++;
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}