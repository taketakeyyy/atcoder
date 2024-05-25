#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll N, T; cin >> N >> T;
    // vector grid(N, vector(N, false));
    vector<ll> numH(N, 0), numW(N, 0); // 各行, 各列の印のついた個数
    vector<ll> numNaname(2, 0); // ななめのやつ
    ll ans = -1;
    for(ll t=0; t<T; t++) {
        ll a; cin >> a;
        a--;
        ll h = a/N;
        ll w = a%N;
        // grid[h][w] = true;
        numH[h]++;
        numW[w]++;
        if (h==w) numNaname[0]++;
        if (h+w == N-1) numNaname[1]++;
        if (ans==-1) {
            if (numH[h]==N) ans = t;
            if (numW[w]==N) ans = t;
            if (numNaname[0]==N) ans = t;
            if (numNaname[1]==N) ans = t;
        }
    }

    if (ans != -1) cout << ans+1 << endl;
    else cout << -1 << endl;

    // ビンゴか？
    // auto f = [&]() -> bool {
    //     // 横の走査
    //     for(ll h=0; h<N; h++) {
    //         bool is_bingo = true;
    //         for(ll w=0; w<N; w++) {
    //             if (grid[h][w]) continue;
    //             is_bingo = false;
    //             break;
    //         }
    //         if (is_bingo) return true;
    //     }

    //     // 縦の走査
    //     for(ll w=0; w<N; w++) {
    //         bool is_bingo = true;
    //         for(ll h=0; h<N; h++) {
    //             if (grid[h][w]) continue;
    //             is_bingo = false;
    //             break;
    //         }
    //         if (is_bingo) return true;
    //     }

    //     {// 左から右への対角線の走査
    //         bool is_bingo = true;
    //         for(ll i=0; i<N; i++) {
    //             if(grid[i][i]) continue;
    //             is_bingo = false;
    //             break;
    //         }
    //         if (is_bingo) return true;
    //     }
    //     {// 右から左への対角線の走査
    //         bool is_bingo = true;
    //         for(ll i=0; i<N; i++) {
    //             if(grid[i][N-1-i]) continue;
    //             is_bingo = false;
    //             break;
    //         }
    //         if (is_bingo) return true;
    //     }
    //     return false;
    // };

    // if (f())
}


int main() {
    solve();
    return 0;
}