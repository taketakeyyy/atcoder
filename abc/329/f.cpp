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
    ll N, Q; cin >> N >> Q;
    vector<ll> C(N);
    vector<unordered_set<ll>> box(N+1);
    for(ll i=0; i<N; i++) {
        cin >> C[i];
        box[i+1].insert(C[i]);
    }

    for(ll q=0; q<Q; q++) {
        ll a, b; cin >> a >> b;
        box[b].merge(box[a]);
        box[a].clear();
        cout << box[b].size() << endl;
    }
}


// マージテク：集合をまとめるとき、大きい方が小さいを方をマージすると計算量がならしO(logN)
void solve2() {
    ll N, Q; cin >> N >> Q;
    vector<ll> C(N);
    vector<unordered_set<ll>> box(N);
    for(ll i=0; i<N; i++) {
        cin >> C[i]; C[i]--;
        box[i].insert(C[i]);
    }

    for(ll q=0; q<Q; q++) {
        ll a, b; cin >> a >> b;
        a--; b--;
        if (box[a].size() > box[b].size()) swap(box[a], box[b]);
        box[b].merge(box[a]);
        box[a].clear();
        cout << box[b].size() << endl;
    }
}


int main() {
    // solve();
    solve2();
    return 0;
}