#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
const long long INF = LONG_LONG_MAX - 1'001'001'001'001'001;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };
//ordered_set
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// 初項a, 末項l, 項数n のときの等差数列の和
ll tousa1(const ll &a, const ll &l, const ll &n) { return ((a+l)*n)/2; }
// 初項a, 公差d, 項数n のときの等差数列の和
ll tousa2(const ll &a, const ll &d, const ll &n) { return ((2*a+(n-1)*d)*n)/2; }


void solve() {
    ll N, M; cin >> N >> M;

    vector<vector<ll>> ans;
    auto dfs = [&](auto dfs, ll idx, vector<ll> &A) -> bool {
        // 終了条件
        if (idx == N) {
            ans.push_back(A);
            return true;
        }

        // 次の探索
        if (idx == 0) {
            for(ll a=1; a<=M; a++) {
                A[idx] = a;
                bool res = dfs(dfs, idx+1, A);
                // if (!res) return false;
            }
        }
        else {
            if (A[idx-1]+10 > M) return false;
            for(ll a=A[idx-1]+10; a<=M; a++) {
                A[idx] = a;
                if (idx+1!=N and a+10>M) return false;
                bool res = dfs(dfs, idx+1, A);
            }
        }
        return false;
    };
    vector<ll> A(N);
    dfs(dfs, 0, A);

    // 出力
    cout << ans.size() << endl;
    for(auto vec: ans) {
        for(ll v: vec) {
            cout << v << " ";
        }
        cout << endl;
    }
}


int main() {
    solve();
    return 0;
}