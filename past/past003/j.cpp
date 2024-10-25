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


void solve() {
    ll N, M; cin >> N >> M;
    vector<ll> A(M);
    for(ll i=0; i<M; i++) cin >> A[i];

    // child[i] := N-i番目の子どもが食べたことのある最大の寿司の美味しさ
    vector<ll> child(N, -INF);
    vector<ll> ans(M);
    for(ll i=0; i<M; i++) {
        ll idx = lower_bound(child.begin(), child.end(), A[i]) - child.begin();
        if (idx == 0) {
            ans[i] = -1;
        }
        else {
            ans[i] = N-idx+1;
            idx--;
            child[idx] = A[i];
        }
    }

    // 出力
    for(ll v: ans) {
        cout << v << endl;
    }
}


int main() {
    solve();
    return 0;
}