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
    ll sx, sy; cin >> sx >> sy;
    vector<ll> X(N), Y(N);
    map<ll,set<ll>> rows, cols;
    for(ll i=0; i<N; i++) {
        cin >> X[i] >> Y[i];
        rows[Y[i]].insert(X[i]);
        cols[X[i]].insert(Y[i]);
    }

    set<pair<ll,ll>> visited;
    for(ll i=0; i<M; i++) {
        char d; cin >> d;
        ll c; cin >> c;
        if (d == 'U') {
            if (cols.count(sx)) {
                auto &st = cols[sx];
                auto it1 = st.lower_bound(sy);
                auto it2 = st.upper_bound(sy+c);
                // 家を破壊する（TLE回避）
                while(it1 != it2) {
                    visited.insert({sx, *it1});
                    it1 = st.erase(it1);
                }
            }
            sy += c;
        }
        else if (d == 'D') {
            if (cols.count(sx)) {
                auto &st = cols[sx];
                auto it1 = st.lower_bound(sy-c);
                auto it2 = st.upper_bound(sy);
                // 家を破壊する
                while(it1 != it2) {
                    visited.insert({sx, *it1});
                    it1 = st.erase(it1);
                }
            }
            sy -= c;
        }
        else if (d == 'L') {
            if (rows.count(sy)) {
                auto &st = rows[sy];
                auto it1 = st.lower_bound(sx-c);
                auto it2 = st.upper_bound(sx);
                // 家を破壊する
                while(it1 != it2) {
                    visited.insert({*it1, sy});
                    it1 = st.erase(it1);
                }
            }
            sx -= c;
        }
        else if (d == 'R') {
            if (rows.count(sy)) {
                auto &st = rows[sy];
                auto it1 = st.lower_bound(sx);
                auto it2 = st.upper_bound(sx+c);
                // 家を破壊する
                while(it1 != it2) {
                    visited.insert({*it1, sy});
                    it1 = st.erase(it1);
                }
            }
            sx += c;
        }
    }
    cout << sx << " " << sy << " " << visited.size() << endl;
}


int main() {
    solve();
    return 0;
}