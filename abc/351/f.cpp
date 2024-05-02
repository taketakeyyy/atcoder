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

#include <atcoder/fenwicktree>

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
pair<map<ll,ll>, map<ll,ll>> coordinate_compression(vector<ll> A) {
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
    return {a2c, c2a};
}

void solve() {
    ll N; cin >> N;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // Aの値を座標圧縮する
    auto[a2c, c2a] = coordinate_compression(A);

    // fenwick treeを作成
    ll fwN = 4e5+1;
    atcoder::fenwick_tree<ll> fwSum(fwN); // A[i]の和
    atcoder::fenwick_tree<ll> fwCnt(fwN); // A[i]の個数
    ll ans = 0;
    for(ll j=0; j<N; j++) {
        ll a = A[j];
        ll c = a2c[a];
        fwSum.add(c, a);
        fwCnt.add(c, 1LL);
        ans += fwCnt.sum(0, c)*a - fwSum.sum(0, c);
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}