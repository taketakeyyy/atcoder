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
    string S, T; cin >> S >> T;
    // Sのほうが長い
    if (S.size() < T.size()) swap(S, T);

    ll SN = S.size();
    ll TN = T.size();
    for(ll i=0; i<SN; i++) {
        if (i >= TN) {
            cout << i+1 << endl;
            return;
        }
        if (S[i] == T[i]) continue;
        cout << i+1 << endl;
        return;
    }
    cout << 0 << endl;
}


int main() {
    solve();
    return 0;
}