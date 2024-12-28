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

/**
 * @brief 配列Aの値を座標圧縮する O(N)
 *
 * @param A
 * @return pair<map<ll,ll>, map<ll,ll>>
 * 以下の2つのmapを返す
 *  a2c[a] := もとの値aをキーにして、座標圧縮後の値cを返すmap
 *  c2a[c] := 座標圧縮後の値cをキーにして、もとの値aを返すmap
 *
 * @example
 *  // Aの値を座標圧縮する A = {1,10,1000,999999,...}
 *  auto[a2c, c2a] = coordinate_compression(A);
 */
tuple<map<ll,ll>, map<ll,ll>, ll> coordinate_compression(vector<ll> A) {
    map<ll,ll> a2c, c2a;
    ll N = A.size();
    sort(A.begin(), A.end());

    ll c = 0; // 座標圧縮した値
    ll pre_a = -INF;
    for(ll i=0; i<N; i++) {
        ll a = A[i];
        if (pre_a != a) {
            a2c[a] = c;
            c++;
            pre_a = a;
        }
    }
    return {a2c, c2a, c};
}

void solve() {
    ll N, M; cin >> N >> M;
    vector<ll> X(M), Y(M);
    vector<char> C(M);
    // map<ll,priority_queue<pair<ll,char>>> rows;
    // map<ll,priority_queue<pair<ll,char>>> cols;
    for(ll i=0; i<M; i++) {
        cin >> X[i] >> Y[i] >> C[i];
        swap(X[i], Y[i]);
    }

    // 座標圧縮する
    auto[Xa2c, Xc2a, XN] = coordinate_compression(X);
    auto[Ya2c, Yc2a, YN] = coordinate_compression(Y);

    vector<priority_queue<pair<ll,char>>> rows(YN);
    vector<priority_queue<pair<ll,char>>> cols(XN);
    for(ll i=0; i<M; i++) {
        ll y = Ya2c[Y[i]];
        ll x = Xa2c[X[i]];
        rows[y].push({x,C[i]});
        rows[x].push({y,C[i]});
    }

    auto f = [&](vector<priority_queue<pair<ll,char>>> rows, vector<priority_queue<pair<ll,char>>> cols) -> bool {
        for(ll y=0; y<(ll)rows.size(); y++) {
            auto &pq = rows[y];
            bool is_now_white = true;
            while(!pq.empty()) {
                auto[x, c] = pq.top(); pq.pop();

                if (c == 'W') {
                    if (!is_now_white) return false;
                    // colsに y以下はすべて白だと 追加する
                    // TODO
                    cols[x].push({y,'W'});
                }
                else {
                    if (is_now_white) {
                        is_now_white = false;

                        // colsに y以下はすべて黒だと 追加する
                        for(ll i=0; i<(ll)cols.size(); i++) {
                            if (i <= x) {
                                cols[i].push({y,'B'});
                            }
                        }
                    }
                }
            }
        }

        for(ll x=0; x<(ll)cols.size(); x++) {
            auto &pq = cols[x];
            ll pre_y = INF;
            char pre_c = 'W';
            bool is_now_white = true;
            while(!pq.empty()) {
                auto[y, c] = pq.top(); pq.pop();
                if (pre_y==y and pre_c==c) continue;
                if (pre_y==y and pre_c!=c) return false;

                if (c == 'W') {
                    if (!is_now_white) return false;
                }
                else {
                    if (is_now_white) {
                        is_now_white = false;
                    }
                }
                pre_y = y;
                pre_c = c;
            }
        }
        return true;
    };

    bool is_ok = f(rows, cols);
    // is_ok &= f(cols, rows);
    if (is_ok) cout << "Yes" << endl;
    else cout << "No" << endl;
}

void solve2() {
    ll N, M; cin >> N >> M;
    vector<tuple<ll,ll,char>> XYC;
    for(ll i=0; i<M; i++) {
        ll x, y; cin >> x >> y;
        char c; cin >> c;
        XYC.push_back({x,y,c});
    }
    sort(XYC.begin(), XYC.end());

    ll mnY = INF; // 白マスの最小Y座標
    for(auto[x, y, c]: XYC) {
        if (c == 'W') {
            chmin(mnY, y);
        }
        else {
            if (mnY <= y) {
                cout << "No" << endl;
                return;
            }
        }
    }
    cout << "Yes" << endl;
    return;
}

int main() {
    // solve();
    solve2();
    return 0;
}