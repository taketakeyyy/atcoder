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


// Aの前後の間にある数字の個数の累積和をとったものをBとする。
// (例)便宜上、Aの最初に0を挿入する
// A: 0 3 5 6 7 10
// B: 0 2 3 3 3  5
// 数列Bには、「何番目の数字まではここまでに出てる」という情報が入っている。
// k番目の数字を求めたいとき、Bに対して二分探索すると、どの間に存在するかを調べられる。
// どの間にあるかわかれば、Aを使ってk番目の数字を求められる。
void solve() {
    ll N, Q; cin >> N >> Q;
    vector<ll> A(N+1, 0);
    for(ll i=1; i<=N; i++) {
        cin >> A[i];
    }

    // Aの前後の間にある数字の個数の累積和をとったものをBとする
    vector<ll> B;
    B.push_back(0);
    for(ll i=1; i<=N; i++) {
        B.push_back(B[i-1] + A[i]-A[i-1]-1);
    }

    // クエリ処理
    for(ll q=0; q<Q; q++) {
        ll k; cin >> k;
        ll idx = lower_bound(B.begin(), B.end(), k) - B.begin();
        idx--;
        ll ans = A[idx] + (k-B[idx]);
        cout << ans << endl;
    }
}


int main() {
    solve();
    return 0;
}