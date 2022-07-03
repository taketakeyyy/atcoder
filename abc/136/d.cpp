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
    // ダブリングで解く
    // この問題、よくよく考えると最悪ケースの RRRRR....RL という長さNの文字列でも左端の子供はN-1回の移動で右端に到達し収束するので、10^100回移動をしなくていい
    string S; cin >> S;
    ll N = S.size();
    const ll D = 21; // 2^20 > 2*10^5

    // functional graph A を作成
    vector<ll> A(N);
    for(ll i=0; i<N; i++) {
        if (S[i] == 'L') {
            A[i] = i-1;
        }
        else {
            A[i] = i+1;
        }
    }

    // ダブリング作成
    auto doubling = make_doubling<ll>(N, D, A);

    // 10^100回の移動後の各マスにいる子供の人数は？
    // たかだか2*10^5回移動すれば、すべての子供はループに突入する。ループのグラフは頂点数2である。
    // なので、10^100回移動する必要はなく、10^100からある程度2の倍数を引いた回数移動すればよい。すなわち、計算可能かつ十分大きい偶数回移動させればよいことになる。
    // ダブリングの最大値2^{D-1}回は、計算可能かつ十分大きい偶数回の移動回数である。
    vector<ll> masu(N, 0);
    for(ll u=0; u<N; u++) {
        masu[doubling[D-1][u]]++;
    }
    for(ll i=0; i<N; i++) {
        cout << masu[i] << " ";
    }
    cout << endl;

}


int main() {
    solve();
    return 0;
}