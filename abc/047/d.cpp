#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/b)
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


// 高橋は、最安値でT/2個買って、最高値でT/2売れば利益は最大になる。
// ただし、街は i から i+1 へ移動するしかないことに注意
// j > i かつ、A[j] - A[i]が最大となる組(j,i)の個数が答え。
// 注意として、(i,j1)と(i,j2)みたいにiが重複している組は、A[i]を変更するだけで青木の目的は果たせる。
// …のだが、制約によりA[i]は相異なるので、そのようなj1とj2は存在しないので、考慮しなくてよい。

// まず j > i かつ、A[j]-A[i]（利益）の最大値はなんなのか？
// 全探索だとO(N^2)なのでだめ。
// 街への移動は左から右しか移動できないことを考えると、
// 高橋が街iでりんごを売るとき、街iより左にある最安値の街で買ったと考えて良い。
// これは、Aを左から右に、最安値を更新しながらシミュレーションすると、利益の最大値が求まる。

// 利益の最大値がmxだとわかったなら、各iについて、りんごの価格がA[i]+mxであり、かつ位置がiより大きい街を探せば良い。
// これはO(N)で求まる。
void solve() {
    ll N, T; cin >> N >> T;
    vector<ll> A(N);
    map<ll,ll> pos;  // A[i]の位置
    for(ll i=0; i<N; i++) {
        cin >> A[i];
        pos[A[i]] = i;
    }

    // j>iかつA[j]-A[i]（利益の最大値）を求める
    ll mx = numeric_limits<ll>::min();
    ll min_a = A[0];
    for(ll i=1; i<N; i++) {
        if (A[i] < min_a) {
            min_a = A[i];
        }
        else {
            mx = max(mx, A[i]-min_a);
        }
    }

    // 利益の最大値がわかったので、各iについて、りんごの価格がA[i]+mxで、かつ位置iより右側にあるような街が存在するかを数える。
    ll ans = 0;
    for(ll i=0; i<N; i++) {
        ll a = A[i] + mx;
        if (pos.count(a) && i < pos[a]) {
            ans++;
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}