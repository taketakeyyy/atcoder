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

// 解説
// dp[x] := 直前に出た目がxである状態で、終了するまでに行う操作の回数の期待値
// 直前に出た目がxのとき、どのサイコロを降るのが最適か？ -> 「各サイコロを降ったときの期待値」を求め、最大のものを選ぶ O(N)
// xの状態数は高々6Nなので、全体の計算量はO(N^2)となり、間に合わない。
// なにかを工夫する必要がある。
// 「各サイコロを降ったときの期待値」を高速化できないか？
// 実は、毎回「各サイコロを降ったときの期待値」を計算する必要はなく、変更箇所はx+1の目を持つサイコロの期待値だけ
void solve() {
    ll N; cin >> N;
    vector A(N, vector<ll>(6));
    vector<ll> eyes;  // サイコロの目
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<6; j++) {
            cin >> A[i][j];
            eyes.push_back(A[i][j]);
        }
    }

    // 各目を[1,6N]の範囲に収める
    sort(eyes.begin(), eyes.end());
    map<ll,ll> eye2idx;
    for(ll i=0; i<6*N; i++) {
        eye2idx[eyes[i]] = i+1;
    }
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<6; j++) {
            A[i][j] = eye2idx[A[i][j]];
        }
    }

    // eye2dice[eye] := サイコロの目eyeを持つサイコロ
    map<ll,ll> eye2dice;
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<6; j++) {
            eye2dice[A[i][j]] = i;
        }
    }

    // メモ化再帰で求める
    // f(x) := 直前に出た目がxである状態で、終了するまでに行う操作の回数の期待値の最大
    map<ll, double> dp; // f(x)のメモ値
    dp[6*N] = 1.0;
    double maxDE = 1.0; // DE[i] := サイコロiを降ったときの期待値とする。maxDEは、各iのDE[i]のうちの最大のもの
    auto f = [&](auto self, ll x) -> double {
        if (dp.count(x)) return dp[x];

        // x+1の目を持つサイコロを降ったときの期待値を計算する
        double expect = 1;
        double p = 1.0/6.0; // 遷移確率
        ll dice = eye2dice[x+1];
        for(ll j=0; j<6; j++) {
            if (x >= A[dice][j]) continue;
            expect += p * self(self, A[dice][j]);
        }
        maxDE = max(maxDE, expect);

        return dp[x] = maxDE;
    };

    printf("%.10f\n", f(f,0));
}


int main() {
    solve();
    return 0;
}