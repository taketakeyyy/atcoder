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
    ll N, K; cin >> N >> K;
    string S; cin >> S;

    vector<vector<string>> T(2);
    string item = "";
    item.push_back(S[0]);
    int now = S[0]-'0';
    for(ll i=1; i<N; i++) {
        char moji = S[i];
        if (int(moji-'0') != now) {
            T[now].push_back(item);
            item.clear();
            item.push_back(moji);
            now = moji - '0';
        }
        else {
            item.push_back(moji);
        }
    }
    if (item.empty() == false) T[now].push_back(item);

    string ans = "";
    now = S[0]-'0';
    int t0_i = 0;
    int t1_i = 0;
    while(1) {
        if (t0_i>=(ll)T[0].size() and t1_i>=(ll)T[1].size()) break;

        if (now==1 and t1_i==K-2) {
            ans += T[1][t1_i++];
            ans += T[1][t1_i++];
            ans += T[0][t0_i++];
            if (t0_i < (ll)T[0].size()) {
                ans += T[0][t0_i++];
            }
            continue;
        }

        if (now == 0) {
            ans += T[0][t0_i++];
            now = 1;
        }
        else {
            ans += T[1][t1_i++];
            now = 0;
        }
    }

    // 出力
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}