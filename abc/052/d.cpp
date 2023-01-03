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


// (1)「初期位置より西の街をすべて回ったあと東の街をすべて回る」
// (2)「初期位置より東の街をすべて回ったあと西の街をすべて回る」
// (1)と(2)は同じことなので、どちらか一方でいい。
// …なのだが、制約により初期位置は最も西の街なので、(2)をする
// 次に、テレポートするか徒歩で次の街に移動するかについて、
// (移動距離)*A < B なら徒歩でいけばよくて、そうでないならテレポート
void solve() {
    ll N, A, B; cin >> N >> A >> B;
    vector<ll> X(N);
    for(ll i=0; i<N; i++) cin >> X[i];

    ll ans = 0;
    for(ll i=1; i<N; i++) {
        if ((X[i]-X[i-1])*A < B) {
            ans += (X[i]-X[i-1])*A;
        }
        else {
            ans += B;
        }
    }

    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}