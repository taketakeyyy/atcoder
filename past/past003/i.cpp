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
    ll N; cin >> N;
    ll Q; cin >> Q;
    map<ll,ll> row, col; // row[i] := i行目を指定されたとき、本当に参照すべき行番号を返す
    for(ll i=1; i<=N; i++) {
        row[i] = i;
        col[i] = i;
    }

    bool isT = false; // 転置してるか
    for(ll q=0; q<Q; q++) {
        ll type; cin >> type;
        if (type == 1) {
            //行の交換
            ll a, b; cin >> a >> b;
            if (isT) swap(col[a], col[b]);
            else swap(row[a], row[b]);
        }
        else if (type == 2) {
            //列の交換
            ll a, b; cin >> a >> b;
            if (isT) swap(row[a], row[b]);
            else swap(col[a], col[b]);
        }
        else if (type == 3) {
            //転置
            isT = !isT;
        }
        else {
            //出力
            ll a, b; cin >> a >> b;
            if (isT) swap(a,b);
            ll i = row[a];
            ll j = col[b];
            ll num = N*(i-1) + j-1;
            cout << num << endl;
        }
    }
}


int main() {
    solve();
    return 0;
}