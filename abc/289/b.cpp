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
    ll N, M; cin >> N >> M;
    vector<ll> G(N+1, -1);
    for(ll i=0; i<M; i++) {
        ll a; cin >> a;
        G[a] = a+1;
    }

    ll i = 1;
    while(i <= N) {
        vector<ll> output;
        output.push_back(i);
        while(G[i] != -1) {
            i = G[i];
            output.push_back(i);
        }
        // 出力
        for(ll j=(ll)output.size()-1; j>=0; j--) {
            cout << output[j] << " ";
        }
        i++;
    }
    cout << endl;
}


int main() {
    solve();
    return 0;
}