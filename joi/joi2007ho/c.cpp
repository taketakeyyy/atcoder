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


/* 面積計算 */
ll area(ll x1, ll y1, ll x2, ll y2) {
    return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}

void solve() {
    ll N; cin >> N;
    vector<pair<ll,ll>> XYs;
    set<pair<ll,ll>> P;  // 点集合
    for(ll i=0; i<N; i++) {
        ll x, y; cin >> x >> y;
        XYs.push_back({x,y});
        P.insert({x,y});
    }
    sort(XYs.begin(), XYs.end());

    // 4つの点a,b,c,dとする。
    // 2点a,bを決めれば、c,dは計算で出せる。
    // c,dが点集合Pに含まれてればOK。
    ll ans = 0;
    for(ll a=0; a<N; a++) {
        auto [ax, ay] = XYs[a];

        for(ll b=a+1; b<N; b++) {
            auto [bx, by] = XYs[b];

            // a,b,c,d は反時計回りにまわるようにすれば、1つに定まる
            ll cx = bx - (by-ay);
            ll cy = by + (bx-ax);
            ll dx = ax - (by-ay);
            ll dy = ay + (bx-ax);

            if (P.count({cx,cy}) && P.count({dx,dy})) {
                ans = max(ans, area(ax,ay,bx,by));
            }
        }
    }

    // 出力
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}