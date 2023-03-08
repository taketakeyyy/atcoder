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
    vector<string> S(N);
    for(ll i=0; i<N; i++) {
        cin >> S[i];
    }
    vector<bool> ans(N, false);
    for(ll i=0; i<M; i++) {
        string T; cin >> T;
        for(ll j=0; j<N; j++) {
            if (S[j].substr(3,3) == T) ans[j] = true;
        }
    }

    // 答え
    ll cnt = 0;
    for(ll i=0; i<N; i++) {
        cnt += (ans[i] ? 1 : 0);
    }
    cout << cnt << endl;
}


int main() {
    solve();
    return 0;
}