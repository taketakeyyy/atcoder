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
    ll K, T; cin >> K >> T;
    vector<ll>A(T);
    rep(i,T) cin >> A[i];
    // 4種類のケーキ: □□□□○○○○●●●●●●●●△△△△△△△△△△△△
    // まず一番多いケーキを並べる: △△△△△△△△△△△△
    // 次に、その次に多いケーキを挟む：●△●△●△●△●△●△●△●△△△△△
    // 次に、その次に多いケーキを挟む：●△●△●△●△●△●△●△●△○△○△○△○△
    // 次に、その次に多いケーキを挟む：□●□△□●△●△●△●△●△●△●△○△○△○△○△□
    // というふうにすれば、必ず連続で食べる日は存在しなくなる。
    // ただし、(一番多いケーキの個数-1) > (それ以外のケーキの総和)のときだけ、連続で食べないといけない
    sort(A.begin(), A.end(), greater<ll>());
    ll rest = accumulate(A.begin(), A.end(), 0LL) - A[0];
    if (A[0]-1 > rest) {
        cout << A[0]-rest-1 << endl;
    }
    else {
        cout << 0 << endl;
    }
}


int main() {
    solve();
    return 0;
}