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
    vector<ll> A(M);
    for(ll i=0; i<M; i++) cin >> A[i];

    priority_queue<pair<ll,ll>> pq; // 大きい順(投票数,番号)
    map<ll,ll> mp;
    for(ll i=0; i<M; i++) {
        mp[A[i]]++;
        pq.push({mp[A[i]], -A[i]});

        // 出力
        auto[ignore, number] = pq.top();
        cout << -number << endl;
    }
}


int main() {
    solve();
    return 0;
}