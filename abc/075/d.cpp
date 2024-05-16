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
    ll N, K; cin >> N >> K;
    vector<pair<ll,ll>> coords(N);
    set<ll> Xset, Yset; // X座標とY座標を列挙する
    for(ll i=0; i<N; i++) {
        ll x, y; cin >> x >> y;
        coords[i] = {x,y};
        Xset.insert(x);
        Yset.insert(y);
    }
    vector<ll> X(Xset.begin(), Xset.end());
    vector<ll> Y(Yset.begin(), Yset.end());

    // 長方形を作る2点を全探索し、長方形内の点を全探索で数える O(N^5)
    ll ans = INF;
    for(ll x1: X) {
        for(ll x2: X) {
            for(ll y1: Y) {
                for(ll y2: Y) {
                    ll s = abs(x2-x1)*abs(y2-y1); // 面積
                    ll minX = min(x1,x2);
                    ll maxX = max(x1,x2);
                    ll minY = min(y1,y2);
                    ll maxY = max(y1,y2);
                    ll cnt = 0; // 長方形内の点の数
                    for(ll k=0; k<N; k++) {
                        auto[x3,y3] = coords[k];
                        if (minX<=x3 and x3<=maxX and minY<=y3 and y3<=maxY) cnt++;
                    }
                    if (cnt >= K) chmin(ans, s);
                }
            }
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}