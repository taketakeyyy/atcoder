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
    ll N; cin >> N;
    ll T; cin >> T;
    string S; cin >> S;
    vector<ll> X(N);
    map<ll,ll> pos; // ←の位置
    for(ll i=0; i<N; i++) {
        cin >> X[i];
        if (S[i]=='0') pos[X[i]]++;
    }

    // posの累積和
    map<ll,ll> ruiPos;
    ruiPos[(ll)-1000000010] = 0;
    ll now = 1;
    for(auto[key, val]: pos) {
        ruiPos[key] = now;
        now++;
    }

    ll ans = 0;
    for(ll i=0; i<N; i++) {
        if (S[i]=='0') continue;

        // [x, x+2T]の範囲を数えたい
        ll l = X[i];
        ll r = l + 2*T;
        auto it1 = ruiPos.lower_bound(l);
        it1--;
        auto it2 = ruiPos.lower_bound(r+1);
        it2--;
        ll cnt = (*it2).second - (*it1).second;
        ans += cnt;
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}