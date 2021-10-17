#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
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


void solve() {
    ll N; cin >> N;

    // 二次元にもす法
    ll const MAX_X = 1000;
    ll const MAX_Y = 1000;
    vector<vector<ll>> imos(MAX_X+1, vector<ll>(MAX_Y+1, 0));
    for(ll i=0; i<N; i++) {
        ll lx, ly, rx, ry; cin >> lx >> ly >> rx >> ry;
        rx--; ry--;
        imos[lx][ly]++;
        imos[rx+1][ry+1]++;
        imos[rx+1][ly]--;
        imos[lx][ry+1]--;
    }

    // 水平方向スキャン
    for(ll x=1; x<MAX_X+1; x++) {
        for(ll y=0; y<MAX_Y+1; y++) {
            imos[x][y] += imos[x-1][y];
        }
    }
    // 垂直方向スキャン
    for(ll y=1; y<MAX_Y+1; y++) {
        for(ll x=0; x<MAX_X+1; x++) {
            imos[x][y] += imos[x][y-1];
        }
    }

    // 紙が重なっている部分の面積を数える
    map<ll,ll> ans;
    for(ll k=0; k<=N; k++) ans[k] = 0;
    for(ll x=0; x<MAX_X; x++) {
        for(ll y=0; y<MAX_Y; y++) {
            ans[imos[x][y]]++;
        }
    }

    // 出力
    for(ll k=1; k<=N; k++) {
        cout << ans[k] << endl;
    }
}


int main() {
    solve();
    return 0;
}