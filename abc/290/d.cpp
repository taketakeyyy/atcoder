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


// 解説AC
void solve() {
    ll T; cin >> T;
    vector<ll> answers;
    for(ll t=0; t<T; t++) {
        ll N, D, K; cin >> N >> D >> K;
        K--;
        ll g = gcd(N,D);
        ll ans;
        if (g == 1) {
            // 互いに素なので、衝突は発生しない
            ans = K*(D%N)%N;
        }
        else {
            // 衝突が発生する
            N /= g;
            D /= g;
            ll block = (K%N)*D%N;
            ll idx = K/N;
            ans = block*g + idx;
        }
        answers.push_back(ans);
    }

    for(ll ans: answers) cout << ans << endl;
}


int main() {
    solve();
    return 0;
}