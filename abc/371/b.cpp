#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1'000'000'007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1'001'001'001'001'001;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll N, M; cin >> N >> M;
    vector<bool> taro(M, false); // taro[i] := 人iは太郎か
    vector<bool> house(N, false); // house[i] := i番目の家には、長男が生まれたか
    for(ll i=0; i<M; i++) {
        ll a; char b;
        cin >> a >> b; a--;
        if (b == 'M') {
            if (!house[a]) {
                house[a] = true;
                taro[i] = true;
            }
        }
    }

    // 答え
    for(ll i=0; i<M; i++) {
        if (taro[i]) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
}


int main() {
    solve();
    return 0;
}