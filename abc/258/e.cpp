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
 *  for(ll k=D-1; k>=0; k--) {
 *      if ((K>>k)&1) {
 *          now = doubling[k][now];
 *      }
 *  }
 *  cout << now << endl;  // K回の遷移後の頂点番号
 */
template<typename T>
vector<vector<T>> make_doubling(T N, T D, vector<T> const &A) {
    // ダブリングのグラフ構築
    vector doubling(D, vector<ll>(N));  // doubling[k][i] := 頂点iから2^k辿った先の頂点は？
    for(ll i=0; i<N; i++) {
        doubling[0][i] = A[i];
    }
    for(ll k=1; k<D; k++) {
        for(ll i=0; i<N; i++) {
            doubling[k][i] = doubling[k-1][doubling[k-1][i]];  // 2^{k}辿った先は、「2^{k-1}辿った先」を2回辿ればよい
        }
    }
    return doubling;
}

void solve() {
    ll N, Q, X; cin >> N >> Q >> X;
    vector<ll> W(N);
    for(ll i=0; i<N; i++) {
        cin >> W[i];
    }

    // 円環は一列にして2倍にして結合 + 累積和 + にぶたん
    ll WSUM = accumulate(W.begin(), W.end(), 0LL);  // 0LLじゃないとバグるきも
    vector<ll>W2 = W;
    W2.insert(W2.end(), W.begin(), W.end());
    vector<ll> ruiseki(N*2+1, 0);
    for(ll i=1; i<=2*N; i++) {
        ruiseki[i] = ruiseki[i-1] + W2[i-1];
    }

    // Functional Graph G作成
    vector<ll> G(N);
    for(ll i=0; i<N; i++) { G[i] = i; }  // 便宜上G[i] = iとしておく
    set<ll> visited;
    map<ll,ll> box;  // box[i] := box[i]のじゃがいもの個数
    ll start = 0;
    while(1) {
        if (visited.count(start)) {break;}
        visited.insert(start);

        // にぶたんで箱に入るじゃがいもの個数を求める
        ll sumn = N*(X/WSUM);
        ll restx = X%WSUM;
        ll l = start;
        ll r = 2*N;
        while(r-l != 1) {
            ll mid = (l+r)/2;
            if (ruiseki[mid]-ruiseki[start] >= restx) {
                r = mid;
            }
            else {
                l = mid;
            }
        }
        if (ruiseki[l]-ruiseki[start] >= restx) {
            sumn += (l-start);
            G[start] = (l)%N;
        }
        else {
            sumn += (r-start);
            G[start] = (r)%N;
        }
        box[start] = sumn;
        start = G[start];
    }

    // ダブリング作成
    const ll D = 61;
    auto doubling = make_doubling<ll>(N, D, G);

    // クエリ処理
    ll now = 0;
    for(ll q=0; q<Q; q++) {
        ll k; cin >> k;
        k--;
        now = 0;
        for(ll d=D-1; d>=0; d--) {
            if ((k>>d)&1) {
                now = doubling[d][now];
            }
        }
        cout << box[now] << endl;
    }
}

void solve_AC() {
    // 解説AC
    ll N, Q, X; cin >> N >> Q >> X;
    vector<ll> W(N);
    for(ll i=0; i<N; i++) {
        cin >> W[i];
    }

    ll WSUM = accumulate(W.begin(), W.end(), 0LL);
    ll rd = X/WSUM;  // 何周するか
    ll restX = X % WSUM;  // Xの残り

    vector<ll> G(N);
    vector<ll> box(N);
    ll sumn = rd*N;
    for(ll i=0; i<N; i++) {
        // 尺取法
        while(restX >= 1) {
            restX -= W[(i+sumn)%N];
            sumn++;
        }
        box[i] = sumn;
        G[i] = (i+box[i])%N;
        restX += W[i];
        sumn--;
    }

    // ダブリング作成
    const ll D = 41;
    auto doubling = make_doubling<ll>(N, D, G);

    // クエリ処理
    for(ll q=0; q<Q; q++) {
        ll k; cin >> k;
        k--;
        ll now = 0;
        for(ll d=D-1; d>=0; d--) {
            if ((k>>d)&1) {
                now = doubling[d][now];
            }
        }
        cout << box[now] << endl;
    }
}

int main() {
    solve();
    // solve_AC();
    return 0;
}