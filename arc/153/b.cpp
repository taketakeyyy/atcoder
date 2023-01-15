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


// 解説AC
// 参考：https://atcoder.jp/contests/arc153/submissions/38032094
// よくわからんかも
void solve() {
    ll H, W; cin >> H >> W;
    vector<string> A(H);
    vector B(H, vector<char>(W));  // 答え用
    for(ll h=0; h<H; h++) {
        cin >> A[h];
    }
    ll Q; cin >> Q;

    // クエリ先読み
    ll h0 = 0;
    ll w0 = 0;
    for(ll q=0; q<Q; q++) {
        ll a, b; cin >> a >> b;

        if (h0 < a) h0 = (a-1) - h0;
        else h0 = (H-1) - h0 + a;

        if (w0 < b) w0 = (b-1) - w0;
        else w0 = (W-1) - w0 + b;
    }

    // 何をしてる？
    // h[i] := Aのi行目が最終的に何行目になるか
    // w[i] := Aのi列目が最終的に何列目になるか
    vector<ll> h(H), w(W);
    bool rev = Q%2;
    if (rev) {
        for(ll k=0; k<H; k++) {
            h[k] = (h0 - k + H) % H;
        }
        for(ll k=0; k<W; k++) {
            w[k] = (w0 - k + W) % W;
        }
    }
    else {
        for(ll k=0; k<H; k++) {
            h[k] = (h0 + k) % H;
        }
        for(ll k=0; k<W; k++) {
            w[k] = (w0 + k) % W;
        }
    }

    // 何をしてる？
    for(ll i=0; i<H; i++) {
        for(ll j=0; j<W; j++) {
            B[h[i]][w[j]] = A[i][j];
        }
    }

    // 出力
    for(ll i=0; i<H; i++) {
        for(ll j=0; j<W; j++) {
            cout << B[i][j];
        }
        cout << endl;
    }
}


int main() {
    solve();
    return 0;
}