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
    map<ll,ll> a2idx;
    map<ll,ll> idx2a;
    for(ll i=0; i<N; i++) {
        ll a; cin >> a;
        a2idx[a] = i+1;
        idx2a[i+1] = a;
    }

    // 1から順に揃える
    vector<pair<ll,ll>> ans;
    for(ll a=1; a<=N; a++) {
        ll a_idx = a2idx[a];
        if (a_idx == a) continue;

        // aとbを入れ替える
        ll b = idx2a[a];
        ll b_idx = a2idx[b];
        a2idx[a] = b_idx;
        a2idx[b] = a_idx;
        idx2a[a_idx] = b;
        idx2a[b_idx] = a;
        if (a_idx > b_idx) swap(a_idx, b_idx);
        ans.push_back({a_idx, b_idx});
    }

    // 答え
    cout << ans.size() << endl;
    for(auto[ai, bi]: ans) {
        cout << ai << " " << bi << endl;
    }
}


int main() {
    solve();
    return 0;
}