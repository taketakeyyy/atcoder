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

ll N, X;
vector<ll> A, B;
bool ans = false;
// memo[i][total] := i種類目の時点で合計値がtotalのとき探索済みか？
vector<vector<bool>> memo;
void dfs(ll i, ll total) {
    // 終了条件
    if (total == X) {
        cout << "Yes" << endl;
        exit(0);
    }
    if (i == N) return;
    if (memo[i][total]) return;

    // i種類目の硬貨をb枚使う
    for(ll b=0; b<=B[i]; b++) {
        total += A[i] * b;
        if (total > X) break;
        dfs(i+1, total);
        total -= A[i] * b;
        memo[i][total] = true;  // 探索済み（そして駄目だった）
    }
}

void solve() {
    cin >> N >> X;
    memo.resize(N);
    for(ll i=0; i<N; i++) {
        memo[i].resize(1e4+1, false);
    }
    A.resize(N); B.resize(N);
    for(ll i=0; i<N; i++) {
        cin >> A[i] >> B[i];
    }

    dfs(0,0);

    cout << "No" << endl;
}

void solve2() {
    cin >> N >> X;
    A.resize(N+1); B.resize(N+1);
    for(ll i=1; i<=N; i++) {
        cin >> A[i] >> B[i];
    }

    // dp[i][x] := i種類目までの硬貨を使って、x円を作れるか？
    vector dp(N+1, vector<bool>(X+1, false));
    dp[0][0] = true;
    for(ll i=1; i<=N; i++) {
        for(ll x=0; x<=X; x++) {
            if (!dp[i-1][x]) continue;
            for(ll b=0; b<=B[i]; b++) {
                // 硬貨をb枚使う
                if (x+A[i]*b > X) break;
                dp[i][x+A[i]*b] = true;
            }
        }
    }

    // 出力
    if (dp[N][X]) cout << "Yes" << endl;
    else cout << "No" << endl;
}

int main() {
    solve();
    // solve2();
    return 0;
}