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


void solve() {
    ll N, K; cin >> N >> K;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    ll ans = INF;
    // 建物A[i]が見える状態にするかbit全探索
    for(ll bit=0; bit<(1<<N); bit++) {
        ll money = 0;  // かかった金額
        ll height = 0;  // 今までの高さ
        ll see = 0;  // 見えている建物の数
        for(ll i=0; i<N; i++) {
            if (i-1>=0) height = max(height, A[i-1]);

            if (bit>>i&1) {
                if (A[i] > height) {
                    see++;
                    height = A[i];
                }
                else {
                    money += (height-A[i])+1;
                    see++;
                    height++;
                }
            }
        }

        if (see >= K) {
            ans = min(ans, money);
        }
    }

    // 出力
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}