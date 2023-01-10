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


// dp[i][score] := i番目の問題まで見て、総合スコアがscoreになるときの最小問題数
// ただし、スコア部分は配列ではなくて、vector<map<ll,ll>>のmapで実装する
// vector<map<ll,ll>> は重いので注意。直前の状態しか必要のないdpなので、iは省略して実装すれば、ギリギリ間に合う
void solve() {
    ll D, G; cin >> D >> G;
    vector<ll> P(D+1), C(D+1);
    for(ll i=1; i<=D; i++) {
        cin >> P[i] >> C[i];
    }

    // dp[i][score] := i番目の問題まで見て、総合スコアがscoreになるときの最小問題数
    // vector<map<ll,ll>> dp(D+1, map<ll,ll>()); // TLE
    map<ll,ll> dp;  // 直前の情報しかいらないのでiは不要
    dp[0] = 0;
    for(ll i=1; i<=D; i++) {  // 高々10
        map<ll,ll> olddp;
        swap(olddp, dp);

        // i番目の問題を解く場合
        for(ll p=0; p<=P[i]; p++) {  // 高々100
            ll plus_score = 100*i*p;  // 100iの問題をp問解く
            if (p == P[i]) plus_score += C[i];
            for(auto[score, _]: olddp) {  // 高々max(p)*D ⇛ 100*10
                ll new_score = min(score+plus_score, G);  // G以下に丸める
                if (!dp.count(new_score)) dp[new_score] = numeric_limits<ll>::max();
                dp[new_score] = min(dp[new_score], olddp[score]+p);
            }
        }
    }

    // 答え
    cout << dp[G] << endl;
}


// 点数はすべて100の倍数なので、1/100する（圧縮）
// Gの最大値は、D=10で、pがすべて100で、cがすべて1000000のときなので、簡単のためにすべての問題の点数が1000点だと仮定して、
// max(G) ＜ (1000*100 + 1000000)*10 ≒ 10^7
void solve2() {
    ll D, G; cin >> D >> G;
    G /= 100;
    vector<ll> P(D+1), C(D+1);
    for(ll i=1; i<=D; i++) {
        cin >> P[i] >> C[i];
        C[i] /= 100;
    }


    // dp[i][score] := i番目の問題まで見て、総合スコアがscoreになるときの最小問題数
    vector<vector<ll>> dp(D+1, vector<ll>(G+1, INF));
    dp[0][0] = 0;
    for(ll i=1; i<=D; i++) {
        for(ll p=0; p<=P[i]; p++) {
            for(ll score=0; score<=G; score++) {
                // p問問題を解く場合(0問も含む)
                ll new_score = score+i*p;
                if (p == P[i]) new_score += C[i];
                new_score = min(new_score, G);  // 最大値をGに丸める
                dp[i][new_score] = min(dp[i][new_score], dp[i-1][score]+p);
            }
        }
    }

    // 答え
    cout << dp[D][G] << endl;
}


int main() {
    // solve();
    solve2();
    return 0;
}