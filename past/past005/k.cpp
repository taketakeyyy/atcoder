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
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    vector<string> S(4);
    for(ll i=0; i<4; i++) {
        cin >> S[i];
    }

    // グリッド内に収まっているか？
    auto is_inside = [&](ll h, ll w) -> bool {
        return (h>=0 && h<4 && w>=0 && w<4);
    };

    // グリッドの状態がstateのときに座標(h,w)に的があるか？
    auto is_hit = [&](ll state, ll h, ll w) -> bool {
        ll d = 4*h + w;
        return state>>d&1;
    };

    // ボールのズレ
    const vector<pair<ll,ll>> nxt = {{1,0}, {-1,0}, {0,1}, {0,-1}, {0,0}};

    // メモ化再帰 f(state) := 現在のグリッドの状態がstateの状態の、終了するまでに投げる回数の期待値の最小値
    vector<double> dp(1<<16, -1); // f(state) のメモ値
    dp[0] = 0;
    auto f = [&](auto self, ll state) -> double {
        if (dp[state] >= 0) return dp[state];

        // 座標(h,w)に投げて、最も期待値の小さいものを採用
        double min_expect = numeric_limits<double>::max();
        for(ll h=0; h<4; h++) {
            for(ll w=0; w<4; w++) {
                double miss = 0; // 停滞確率
                double p = 1.0/5; // 遷移確率
                double expect = 1; // 期待値
                for(auto[dh, dw]: nxt) {
                    ll nh = h + dh;
                    ll nw = w + dw;
                    if (is_inside(nh,nw)) {
                        if (!is_hit(state, nh, nw)) {
                            // 的がないので外れ
                            miss += p;
                        }
                        else {
                            // 的に当たった
                            ll d = 4*nh + nw;
                            expect += p * self(self, state^(1<<d));
                        }
                    }
                    else {
                        // グリッド外で外れ
                        miss += p;
                    }
                }
                expect /= 1.0-miss;
                min_expect = min(min_expect, expect);
            }
        }

        return dp[state] = min_expect;
    };

    // グリッドの初期状態init_stateを作る
    ll init_state = 0;
    for(ll h=0; h<4; h++) {
        for(ll w=0; w<4; w++) {
            if (S[h][w] == '#') {
                ll d = 4*h + w;
                init_state |= (1<<d);
            }
        }
    }

    // 答え
    printf("%.10f\n", f(f, init_state));
}


int main() {
    solve();
    return 0;
}