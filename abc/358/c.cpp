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
    ll N, M; cin >> N >> M;
    vector<string> S(N);
    for(ll i=0; i<N; i++) cin >> S[i];

    ll ans = INF;
    for(ll bit=0; bit<(1<<N); bit++) {
        ll ppcnt = __builtin_popcountll(bit);

        unordered_set<ll> us;
        for(ll d=0; d<N; d++) {
            if (bit>>d&1) {
                for(ll m=0; m<M; m++) {
                    if (S[d][m] == 'o') us.insert(m);
                }
            }
        }

        if (us.size() == M) {
            chmin(ans, ppcnt);
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}