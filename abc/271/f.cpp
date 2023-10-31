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


// 半分全列挙
void solve() {
    ll N; cin >> N;
    vector<vector<ll>> grid(N, vector<ll>(N));
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<N; j++) cin >> grid[i][j];
    }

    // P[i] := 下にi回移動した状態の、作れる通ったマスの排他的論理和の分布
    vector<unordered_map<ll,ll>> P1(N);
    { // (1,1)からN-1回の移動で作れるもの
        for(ll bit=0; bit<(1<<(N-1)); bit++) {
            ll h=0, w=0; // 現在の座標
            ll num = 0; // 下に移動した回数
            ll total = grid[h][w]; // 排他的論理和
            for(ll d=0; d<N-1; d++) {
                if(bit>>d&1) {
                    num++;

                    h++;
                }
                else {
                    w++;
                }
                total ^= grid[h][w];
            }
            P1[num][total]++;
        }
    }
    vector<unordered_map<ll,ll>> P2(N);
    { //(N,N)からN-1回の移動で作れるもの
        for(ll bit=0; bit<(1<<(N-1)); bit++) {
            ll h=N-1, w=N-1;
            ll num = 0;
            ll total = grid[N-1][N-1];
            for(ll d=0; d<(N-1); d++) {
                if (bit>>d&1) {
                    num++;
                    h--;
                }
                else {
                    w--;
                }
                if (d!=N-2) total ^= grid[h][w]; // 最後の移動のときは足さない
            }
            P2[num][total]++;
        }
    }

    // 条件を満たすものを数え上げる
    ll ans = 0;
    for(ll num1=0; num1<=N-1; num1++) { // 高々N-1回
        auto mp1 = P1[num1];
        auto mp2 = P2[N-1-num1];
        for(auto [key1, val1]: mp1) { // 高々2^{N-1}回
            ans += mp1[key1]*mp2[key1];
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}