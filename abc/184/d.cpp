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



void solve2() {
    /* 解説AC */
    const int X = 100;
    // dp[i][j][k]:=
    vector<vector<vector<double>>> dp(X+1, vector<vector<double>>(X+1, vector<double>(X+1, 0)));
    int a, b, c;
    cin >> a >> b >> c;

    for (int i=X-1; i>=0; --i) {
        for (int j=X-1; j>=0; --j) {
            for (int k=X-1; k>=0; --k) {
                if (i+j+k==0) continue;
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

int main(int argc, char const *argv[]){
    solve2();
    return 0;
}