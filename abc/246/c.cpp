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


// すべての商品を買うので、できるだけクーポンで引ける値が多くなればよい。
// 商品価格をクーポンで引いた値がマイナス値になる場合、0に丸められるが、この場合損をする。
// できるだけ損がないようにクーポンを消費すればいい。
void solve() {
    ll N, K, X; cin >> N >> K >> X;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // 商品の値段をできるだけ0に近くする
    for(ll i=0; i<N; i++) {
        if (K == 0) break;

        ll cnt = A[i]/X;
        if (cnt <= K) {
            A[i] -= cnt*X;
            K -= cnt;
        }
        else {
            A[i] -= K*X;
            K = 0;
        }
    }

    // まだクーポンが余っているなら、商品価格を降順にならべた順に使っていく
    if (K >= 1) {
        sort(A.begin(), A.end());
        reverse(A.begin(), A.end());

        for(ll i=0; i<N; i++) {
            if (K == 0) break;
            K--;
            A[i] = 0;
        }
    }

    // 商品価格の合計を算出する
    ll ans = 0;
    for(ll i=0; i<N; i++) {
        ans += A[i];
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}