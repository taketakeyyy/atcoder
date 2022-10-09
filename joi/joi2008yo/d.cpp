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


// 星空写真の各点を始点にして、星座が作れるか走査すればよい。
void solve() {
    ll M; cin >> M;
    vector<pair<ll,ll>> seiza;  // 星座の座標
    for(ll i=0; i<M; i++) {
        ll x, y; cin >> x >> y;
        seiza.push_back({x,y});
    }
    ll N; cin >> N;
    vector<pair<ll,ll>> pic;  // 写真の座標
    set<pair<ll,ll>> picP;  // 写真の点集合
    for(ll i=0; i<N; i++) {
        ll x, y; cin >> x >> y;
        pic.push_back({x,y});
        picP.insert({x,y});
    }

    // 星空写真の各点を始点にして、星座が作れるか全探索O(NM logN)
    for(ll i=0; i<N; i++) {
        auto[x, y] = pic[i];

        bool is_ok = true;
        for(ll j=1; j<M; j++) {
            auto[prex, prey] = seiza[j-1];
            auto[nx, ny] = seiza[j];
            x += (nx-prex);
            y += (ny-prey);
            if (picP.count({x,y})) continue;
            is_ok = false; break;
        }

        if (is_ok) {
            cout << pic[i].first-seiza[0].first << " " << pic[i].second-seiza[0].second << endl;
            return;
        }
    }
}


int main() {
    solve();
    return 0;
}