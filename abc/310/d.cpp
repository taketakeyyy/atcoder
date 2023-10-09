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
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


// 解説AC
// i人目の人は、既存のチームに入るか、新しいチームを作るか
void solve() {
    ll N, T, M; cin >> N >> T >> M;
    vector<pair<ll,ll>> AB(M);
    vector<vector<ll>> G(N);
    for(ll i=0; i<M; i++) {
        ll a, b; cin >> a >> b;
        a--; b--;
        AB[i] = {a,b};
        G[a].push_back(b);
        G[b].push_back(a);
    }
}


int main() {
    solve();
    return 0;
}