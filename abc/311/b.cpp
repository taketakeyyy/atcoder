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


void solve() {
    ll N, D; cin >> N >> D;
    vector<string> S(N);
    for(ll i=0; i<N; i++) {
        cin >> S[i];
    }

    ll ans = 0;
    ll seq = 0;
    for(ll j=0; j<D; j++) {
        bool is_hima = true;
        for(ll i=0; i<N; i++) {
            if (S[i][j] == 'x') {
                is_hima = false;
                break;
            }
        }

        if (is_hima) {
            seq++;
            ans = max(ans, seq);
        }
        else {
            seq = 0;
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}