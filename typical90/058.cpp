#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 100000
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


ll sum_digits(ll n) {
    // 各桁の和を返す
    ll ret = 0;
    while(n!=0) {
        ret += n%10;
        n /= 10;
    }
    return ret;
}

ll func(ll x) {
    // 一連の処理をする
    ll y = sum_digits(x);
    ll z = (x+y)%MOD;
    return z;
}


void solve1() {
    // [方針]
    // 周期があるとしか考えられない。なぜならzは [0, 10^5-1] の範囲をループするMODの世界だから。たかだか周期は10^5のはず。
    // 周期を考えるときは、必ずしも0の形をした周期とは限らず、6の形をした周期になることもある。注意。

    ll N, K; cin >> N >> K;
    vector<ll> G(1e5);  // G[i] := 頂点iが隣接している頂点番号
    vector<ll> timestamp(1e5);  // timestamp[i] := 頂点iにはじめて到達した時刻
    set<ll> visited;
    ll now = N;
    ll time = 0;
    while(1) {
        if (visited.count(now)) break;
        visited.insert(now);
        timestamp[now] = time;

        ll nxt = func(now);
        G[now] = nxt;
        now = nxt;
        time++;
    }

    ll loop_start = now;  // ループ始まりの頂点
    ll loop_len = time - timestamp[now];  // ループ長（周期）
    if (timestamp[loop_start] >= K) {
        // しっぽをK回たどる
        now = N;
        for(ll i=0; i<K; i++) {
            now = G[now];
        }
        cout << now << endl;
    }
    else {
        // ループに突入するので、周期を利用して必要な移動回数を減らしておく
        ll restK = (K-timestamp[loop_start])%loop_len;  // 残りの移動回数
        now = loop_start;
        for(ll i=0; i<restK; i++) {
            now = G[now];
        }
        cout << now << endl;
    }
}

/**
 * @brief ダブリングの作成
 *
 * @param N T グラフの頂点数
 * @param D T ダブリングの個数。2^60あれば十分なら、D=60
 * @param A vector<T> A[i] := 頂点iの遷移先
 * @return vector<vector<T>>
 *
 * @example
 *  // ダブリングのグラフ構築
 *  ll D = 60;
 *  vector doubling = make_doubling<ll>(N, D, A);
 *
 *  // ダブリングを使ってK回の遷移先を求める
 *  ll now = 0;  // 開始の頂点番号
 *  for(ll d=D-1; d>=0; k--) {
 *      if ((K>>d)&1) {
 *          now = doubling[d][now];
 *      }
 *  }
 *  cout << now << endl;  // K回の遷移後の頂点番号
 */
template<typename T>
vector<vector<T>> make_doubling(T N, T D, vector<T> const &A) {
    // ダブリングのグラフ構築
    vector doubling(D, vector<ll>(N));  // doubling[d][i] := 頂点iから2^d辿った先の頂点は？
    for(ll i=0; i<N; i++) {
        doubling[0][i] = A[i];
    }
    for(ll d=1; d<D; d++) {
        for(ll i=0; i<N; i++) {
            doubling[d][i] = doubling[d-1][doubling[d-1][i]];  // 2^{d}辿った先は、「2^{d-1}辿った先」を2回辿ればよい
        }
    }
    return doubling;
}

void solve2() {
    // ダブリングで解く
    ll N, K; cin >> N >> K;
    vector<ll> G(1e5);  // G[i] := 頂点iに隣接している頂点番号

    ll now = N;
    set<ll> visited;
    while(1) {
        if (visited.count(now)) { break; }
        visited.insert(now);
        ll nxt = func(now);
        G[now] = nxt;
        now = nxt;
    }

    const ll D = 61;  // 2^60 >= 1e18 なので十分
    auto doubling = make_doubling<ll>(1e5, D, G);
    now = N;
    for(ll d=D-1; d>=0; d--) {
        if (K>>d&1) {
            now = doubling[d][now];
        }
    }
    cout << now << endl;
}


int main() {
    solve1();
    // solve2();
    return 0;
}