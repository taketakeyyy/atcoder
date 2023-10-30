#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using pii = pair<int,int>;
const int INF = 1001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


map<tuple<double, double, double>, double> memo;


double dfs(double a, double b, double c, char which, double p, double op) {
    /***
     * a: Aの数
     * b: Bの数
     * c: Cの数
     * which: A,B,Cどれが選ばれたか
     * p: 確率
     * op: 操作回数
     * */
    vector<double> v = {a, b, c};
    sort(v.begin(), v.end());
    tuple<double, double, double> key(v[0], v[1], v[2]);

    if (memo.count(key)) return memo[key];

    if (which=='a' && a==100) {
        return p;
    }
    else if (which=='b' && b==100) {
        return p;
    }
    else if (which=='c' && c==100) {
        return p;
    }

    double ret1 = dfs(a+1, b, c, 'a', p*(a/(a+b+c)), op+1);
    double ret2 = dfs(a, b+1, c, 'b', p*(b/(a+b+c)), op+1);
    double ret3 = dfs(a, b, c+1, 'c', p*(c/(a+b+c)), op+1);
    memo[key] = (ret1+ret2+ret3);
    return (ret1+ret2+ret3)*op;
}


void solve(){
    double A, B, C;
    cin >> A >> B >> C;

    double ans;
    ans = dfs(A, B, C, 'x', (double)1, (double)1);
    cout << fixed << setprecision(6) << ans << endl;
}



// 解説AC
void solve2() {
    const int X = 100;
    // dp[i][j][k]:=金貨i枚、銀貨j枚、銅貨k枚ある状態からの期待値
    //             = dp[i+1][j][k]*(i/(i+j+k))
    //              +dp[i][j+1][k]*(j/(i+j+k))
    //              +dp[i][j][k+1]*(k/(i+j+k))
    //              +1(1手進める)
    vector<vector<vector<double>>> dp(X+1, vector<vector<double>>(X+1, vector<double>(X+1, 0)));
    int a, b, c;
    cin >> a >> b >> c;

    for (int i=X-1; i>=0; --i) {
        for (int j=X-1; j>=0; --j) {
            for (int k=X-1; k>=0; --k) {
                if (i+j+k==0) continue;  // 分母が0になるので
                double now = 0;
                now += dp[i+1][j][k]*i;
                now += dp[i][j+1][k]*j;
                now += dp[i][j][k+1]*k;
                dp[i][j][k] = now/(i+j+k) + 1;
            }
        }
    }
    double ans = dp[a][b][c];
    printf("%.10f\n", ans);
    return;
}


// 期待値DPの解法
void solve3() {
    ll A, B, C; cin >> A >> B >> C;

    // dp[a][b][c] := 現在の硬貨の枚数が(a,b,c)の状態での、終了するまでの操作回数の期待値
    vector dp(101, vector<vector<double>>(101, vector<double>(101, 0)));

    // dpを降順に埋める
    for(ll a=99; a>=A; a--) {
        for(ll b=99; b>=B; b--) {
            for(ll c=99; c>=C; c--) {
                double p1 = (double)a/(a+b+c);
                double p2 = (double)b/(a+b+c);
                double p3 = (double)c/(a+b+c);
                dp[a][b][c] += (1+dp[a+1][b][c])*p1 + (1+dp[a][b+1][c])*p2 + (1+dp[a][b][c+1])*p3;
            }
        }
    }
    printf("%.10lf\n", dp[A][B][C]);
}

// メモ化再帰の解法
void solve4() {
    ll A, B, C; cin >> A >> B >> C;

    // メモ化再帰 f(a,b,c) := 現在の硬貨の枚数が(a,b,c)の状態での、終了するまでの操作回数の期待値
    vector memo(101, vector<vector<double>>(101, vector<double>(101, -1)));
    auto f = [&](auto self, ll a, ll b, ll c) -> double {
        if(a==100 || b==100 || c==100) return 0;
        if (memo[a][b][c] != -1) return memo[a][b][c];

        double p1 = (double)a/(a+b+c);
        double p2 = (double)b/(a+b+c);
        double p3 = (double)c/(a+b+c);
        return memo[a][b][c] = (1+self(self,a+1,b,c))*p1 + (1+self(self,a,b+1,c))*p2 + (1+self(self,a,b,c+1))*p3;
    };

    // 出力
    printf("%.10lf\n", f(f,A,B,C));
}

int main(){
    // solve2();
    solve3();
    // solve4();
    return 0;
}