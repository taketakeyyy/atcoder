#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) (a+(b-1))/b
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }

void solve() {
    ll N, A; cin >> N >> A;
    vector<ll> X(N+1);
    for(int i=1; i<N+1; i++) { cin >> X[i]; }

    // dp[i][k][s] := 左からi枚まで使い、k枚選んだときに和がsになる場合の数
    const ll S_MAX = N*50;
    vector<vector<vector<ll>>> dp(N+1, vector<vector<ll>>(N+1, vector<ll>(S_MAX+1, 0)));
    dp[0][0][0] = 1;
    for(int i=1; i<N+1; i++) {
        for(int k=0; k<=i; k++) {
            for(int s=0; s<=S_MAX; s++) {
                if (s+X[i]<=S_MAX && k-1>=0) {
                    dp[i][k][s+X[i]] += dp[i-1][k-1][s];  // 選んだとき
                }
                dp[i][k][s] += dp[i-1][k][s];  // 選ばなかったとき
            }
        }
    }

    ll ans = 0;
    for(int k=1; k<N+1; k++) {
        if (A*k<=S_MAX) {
            ans += dp[N][k][A*k];
        }
    }

    cout << ans << endl;
}

void make_mp(vector<map<ll,ll>> &mp, const vector<ll> &X) {
    // mpを作る
    for(int bit=0; bit<1<<(X.size()); bit++) {
        ll total = 0;
        ll cnt = 0;
        for(int d=0; d<(int)(X.size()); d++) {
            if (bit>>d&1) {
                cnt++;
                total += X[d];
            }
        }
        mp[cnt][total]++;
    }
}

void solve2() {
    // 半分全列挙で間に合うと思ったら間に合わないんだよなぁTLE
    ll N, A; cin >> N >> A;
    vector<ll> X1;
    vector<ll> X2;
    if (N%2==0) {
        X1.resize(N/2);
        X2.resize(N/2);
    }
    else {
        X1.resize(N/2);
        X2.resize(N/2+1);
    }
    for(int i=0; i<(int)(X1.size()); i++) {
        cin >> X1[i];
    }
    for(int i=0; i<(int)(X2.size()); i++) {
        cin >> X2[i];
    }

    // 半分全列挙なら最大ステップ2^25で間に合う
    vector<map<ll,ll>> mp1;  // mp[n][a] := n個選んだときに作れる整数はaで、その個数
    vector<map<ll,ll>> mp2;
    mp1.resize(X1.size()+1);
    mp2.resize(X2.size()+1);
    make_mp(mp1, X1);
    make_mp(mp2, X2);

    ll ans = 0;
    for(int i=0; i<=(int)X1.size(); i++) {  // 高々 25
        for(int j=0; j<=(int)X2.size(); j++) {  // 高々25
            if (i==0 && j==0) continue;
            for(auto [key1, val1]: mp1[i]) {  // 高々3*10^7
                ll key2 = (i+j)*A - key1;
                if (mp2[j].count(key2)) {
                    ll val2 = mp2[j][key2];
                    ans += val1*val2;
                }
            }
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}