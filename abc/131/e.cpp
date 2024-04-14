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

    // Kは上限以下？
    if (K > (N-1)*(N-2)/2) {
        cout << -1 << endl;
        return;
    }

    // スターグラフを作る
    ll shortNum = (N-1)*(N-2)/2; // 最短距離が2の頂点対(i,j)の数
    vector<pair<ll,ll>> edge;
    for(ll i=1; i<=N-1; i++) {
        edge.push_back({i,N});
    }

    // 最短距離が2の頂点対の個数がK個になるように、1個ずつ辺を張っていく
    ll l=1, r=2;
    while(shortNum!=K) {
        edge.push_back({l,r});
        r++;
        if (r==N) {
            l++; r=l+1;
        }
        shortNum--;
    }

    // 答え
    cout << edge.size() << endl;
    for(auto[u,v]: edge) {
        cout << u << " " << v << endl;
    }
}


int main() {
    solve();
    return 0;
}