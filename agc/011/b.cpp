#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) (a+(b-1))/b
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve() {
    ll N; cin >> N;
    vector<ll>A(N);
    rep(i,N) cin >> A[i];
    // 生き物の大きさを昇順にソートして、番号を振り直しても問題はない
    // A = [1,2,3,4,5,6,7...] のようになる
    // 吸収する側の色が保持されることに注目する
    // A[0]~A[i]の総和の2倍がA[i+1]以下であるなら、iの色を保持したままA[i+1]を吸収できる。そして「i以下の色は必ず作れる」ことが確定する
    // そうでなければ、A[i+1]がA[0]~A[i+1]を吸収する。i+1の色になって、大きさはA[0]~A[i+1]の総和になる。そして「i以下の色は必ず作れない」ことが確定する
    sort(A.begin(), A.end());
    ll total = A[0];
    ll x = 0;  // x番目の生き物の色は作れる状態
    for(int i=1; i<N; i++) {
        if (!(A[i] <= 2*total)) {
            x = i;
        }
        total += A[i];
    }
    cout << N - x << endl;
}


int main() {
    solve();
    return 0;
}