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

// dp用データ
struct Data {
    ll val; // 価値の総和の最大値
    ll col; // 最後に残したボールの色
    Data(ll v=-INF, ll c=-1): val(v), col(c) {}
};

// 上位2つのデータ
struct Top2 {
    Data a; // 価値の総和の最大値が1位のデータ
    Data b; // 価値の総和の最大値が2位のデータ
    Top2(Data _a=Data(-INF,-1), Data _b=Data(-INF,-2)): a(_a), b(_b) {}

    // 新しいデータdを追加して、上位2のデータを更新する
    void update(Data d) {
        if (b.val < d.val) {
            swap(b, d);
            if (a.val < b.val) swap(a, b);
        }
        // 上位2つのデータは、色は必ず異なるようにする
        if (a.col == b.col) b = d; // dを繰り上げ2位にする
    }

    void update(Top2 t) {
        this->update(t.a);
        this->update(t.b);
    }

    // 今回のボールの色がcのとき、適した価値を返す
    ll get(ll c) {
        if (a.col != c) return a.val;
        return b.val;
    }
};

// 解説AC
void solve() {
    ll N, K; cin >> N >> K;
    vector<ll> C(N), V(N);
    for(ll i=0; i<N; i++) {
        cin >> C[i] >> V[i];
    }

    // dp[i][k] := i番目まで見て、取り除いたボールの数がk個のときの、上位2個のデータ
    vector<Top2> dp(K+1);
    dp[0] = Top2(Data(0,-1));
    for(ll i=0; i<N; i++) {
        vector<Top2> olddp(K+1);
        swap(dp, olddp);
        for(ll k=0; k<=K; k++) {
            // ボールを取り除く場合
            if (k < K) dp[k+1] = olddp[k];

            // ボールを残す場合
            ll oldv = olddp[k].get(C[i]);
            if (oldv != -INF) {
                dp[k].update(Data(oldv+V[i], C[i]));
            }
        }
    }

    // 答え
    ll ans = dp[K].a.val;
    if (ans == -INF) cout << -1 << endl;
    else cout << ans << endl;
}


int main() {
    solve();
    return 0;
}