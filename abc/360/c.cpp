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
    vector<ll> A(N), W(N);
    for(ll i=0; i<N; i++) {
        cin >> A[i]; A[i]--;
    }
    for(ll i=0; i<N; i++) cin >> W[i];

    // box[i] := 箱iの中に入っている荷物の重さの集合
    vector<multiset<ll>> box(N);
    for(ll i=0; i<N; i++) {
        box[A[i]].insert(W[i]);
    }

    ll ans = 0;
    for(ll i=0; i<N; i++) {
        while(box[i].size() >= 2) {
            auto it = box[i].begin();
            ans += *it;
            box[i].erase(it);
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}