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


// 木の直径の求め方
// (1)適当な始点aから最短経路計算して、最も遠かった点bを見つける
// (2)点bから最短経路計算して、最も遠かった距離が木の直径
//
// ということで、適当な点から最も遠かった点bを求めて、
// そこから最も遠かった距離が答え
// Nの最大値は50。
// クエリ回数は(1)がN-1回、(2)がN-1回なので、質問回数の上限値100以内に収まる
void solve() {
    ll N; cin >> N;
    ll b = -1;  // 最も遠かった点b
    ll b_dist = -1;
    for(ll i=2; i<=N; i++) {
        // 適当な始点は1とする
        cout << "? " << 1 << " " << i << endl;
        ll dist; cin >> dist;
        if (dist > b_dist) {
            b=i; b_dist=dist;
        }
    }

    // 点bから最も遠い距離を求める
    ll ans = -1;
    for(ll i=1; i<=N; i++) {
        if (i == b) continue;
        cout << "? " << b << " " << i << endl;
        ll dist; cin >> dist;
        ans = max(ans, dist);
    }
    cout << "! " << ans << endl;
}


int main() {
    solve();
    return 0;
}