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
    vector<ll> C(M);
    vector<set<ll>> S(M);
    for(ll i=0; i<M; i++) {
        cin >> C[i];
        for(ll j=0; j<C[i]; j++) {
            ll a; cin >> a;
            S[i].insert(a);
        }
    }

    // bit全探索
    ll ans = 0;
    for(ll bit=1; bit<(1<<M); bit++) {
        set<ll> xset;  // xの集合
        for(ll d=0; d<M; d++) {
            if (bit>>d&1) {
                for(auto a: S[d]) xset.insert(a);
            }
        }

        if ((ll)xset.size() == N) ans++;
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}