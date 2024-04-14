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
    ll N, Q; cin >> N >> Q;
    vector<string> grid(N);
    for(ll i=0; i<N; i++) {
        cin >> grid[i];
    }

    // 累積和の作成
    vector<vector<ll>> ruiA(N+1, vector<ll>(N+1, 0));
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<N; j++) {
            if (grid[i][j] == 'B') ruiA[i+1][j+1] = 1;
        }
    }
    // 横方向の累積
    for(ll i=1; i<=N; i++) {
        for(ll j=1; j<=N; j++) {
            ruiA[i][j] += ruiA[i][j-1];
        }
    }
    // 縦方向の累積
    for(ll j=1; j<=N; j++) {
        for(ll i=1; i<=N; i++) {
            ruiA[i][j] += ruiA[i-1][j];
        }
    }

    // 黒色を数える
    auto calc_black = [&](ll h, ll w) -> ll {
        return ruiA[N][N]*(w/N)*(h/N) + ruiA[h%N][N]*(w/N) + ruiA[N][w%N]*(h/N) + ruiA[h%N][w%N];
    };

    // クエリ処理
    for(ll q=0; q<Q; q++) {
        ll a, b, c, d; cin >> a >> b >> c >> d;
        a++; b++; c++; d++;
        cout << calc_black(c,d) - calc_black(c,b-1) - calc_black(a-1,d) + calc_black(a-1,b-1) << endl;
    }
}


int main() {
    solve();
    return 0;
}