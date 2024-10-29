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
    string S; cin >> S;
    ll Q; cin >> Q;
    map<char,char> mp;
    for(ll q=0; q<Q; q++) {
        char c, d; cin >> c >> d;
        for(auto&[key, moji]: mp) {
            if (moji == c) moji = d;
        }
        if (!mp.contains(c)) mp[c] = d;
    }

    // 置換
    for(char &c: S) {
        if (mp.contains(c)) c = mp[c];
    }
    cout << S << endl;
}


int main() {
    solve();
    return 0;
}