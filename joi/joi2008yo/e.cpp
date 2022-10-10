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
    ll R, C; cin >> R >> C;
    vector<vector<ll>> A(R, vector<ll>(C, 0));
    for(ll i=0; i<R; i++) {
        for(ll j=0; j<C; j++) {
            cin >> A[i][j];
        }
    }

    // R側を裏返すかbit全探索
    ll ans = 0;
    for(ll bit=0; bit<(1<<R); bit++) {
        ll total = 0;

        for(ll c=0; c<C; c++) {
            // 各列において、表の数を数える
            ll head = 0;
            for(ll r=0; r<R; r++) {
                if (bit>>r&1) head += A[r][c] ^ 1;
                else head += A[r][c];
            }

            // 裏の数を計上する。列を裏返したほうが良い場合はそうする
            total += max(head, R-head);
        }

        ans = max(ans, total);
    }

    // 出力
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}