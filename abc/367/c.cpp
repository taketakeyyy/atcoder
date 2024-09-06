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
    ll N, K; cin >> N >> K;
    vector<ll> R(N);
    for(ll i=0; i<N; i++) cin >> R[i];

    auto dfs = [&](auto dfs, ll depth, vector<ll> &A, ll total) {
        // 終了条件
        if (depth == N) {
            if (total%K != 0) return;

            for(ll i=0; i<N; i++) cout << A[i] << " ";
            cout << endl;
            return;
        }

        // 次の探索
        for(ll a=1; a<=R[depth]; a++) {
            total += a;
            A.push_back(a);
            dfs(dfs, depth+1, A, total);
            total -= a;
            A.pop_back();
        }
    };
    vector<ll> A;
    dfs(dfs, 0, A, 0);
}


int main() {
    solve();
    return 0;
}