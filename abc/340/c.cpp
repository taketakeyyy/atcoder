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


void solve2() {
    ll N; cin >> N;

    priority_queue<ll> pq;
    pq.push(N);
    ll ans = 0;
    while(1) {
        ll u = pq.top(); pq.pop();
        if (u < 2) break;

        ans += u;
        pq.push(u/2);
        pq.push(intceil(u,2));
    }
    cout << ans << endl;
}

void solve() {
    ll N; cin >> N;

    map<ll,ll> memo;
    memo[1] = 0;
    memo[0] = 0;
    auto dfs = [&](auto dfs, ll n) {
        if (memo.count(n)) return memo[n];

        ll res1 = dfs(dfs, n/2);
        memo[n/2] = res1;
        ll res2 = dfs(dfs, intceil(n,2));
        memo[intceil(n,2)] = res2;
        ll res = res1 + res2 + n;
        memo[n] = res;
        return memo[n];
    };
    ll ans = dfs(dfs, N);
    cout << ans << endl;
}

int main() {
    solve();
    return 0;
}