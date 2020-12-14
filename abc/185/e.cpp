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
struct mint {
    ll x; // typedef long long ll;
    mint(ll x=0):x((x%MOD+MOD)%MOD){}
    mint operator-() const { return mint(-x);}
    mint& operator+=(const mint a) {
        if ((x += a.x) >= MOD) x -= MOD;
        return *this;
    }
    mint& operator-=(const mint a) {
        if ((x += MOD-a.x) >= MOD) x -= MOD;
        return *this;
    }
    mint& operator*=(const mint a) { (x *= a.x) %= MOD; return *this;}
    mint operator+(const mint a) const { return mint(*this) += a;}
    mint operator-(const mint a) const { return mint(*this) -= a;}
    mint operator*(const mint a) const { return mint(*this) *= a;}
    mint pow(ll t) const {
        if (!t) return 1;
        mint a = pow(t>>1);
        a *= a;
        if (t&1) a *= *this;
        return a;
    }

    // for prime MOD
    mint inv() const { return pow(MOD-2);}
    mint& operator/=(const mint a) { return *this *= a.inv();}
    mint operator/(const mint a) const { return mint(*this) /= a;}
};


void solve(){
    int N, M;
    cin >> N >> M;
    vector<int> A(N), B(M);
    for (int i=0; i<N; i++) {
        cin >> A[i];
    }
    for (int i=0; i<M; i++) {
        cin >> B[i];
    }
    vector<vector<int>> dp(N+1, vector<int>(M+1, INT_MAX-100));
    dp[0][0] = 0;

    for (int i=0; i<N+1; i++) {
        for (int j=0; j<M+1; j++) {
            if (i < N) dp[i+1][j] = min(dp[i+1][j], dp[i][j]+1);  // A[i]を削除する
            if (j < M) dp[i][j+1] = min(dp[i][j+1], dp[i][j]+1);  // B[j]を削除する
            if (i < N && j < M) {  // A[i],B[j]はそのまま
                int cost = 0;
                if (A[i] != B[j]) cost = 1;
                dp[i+1][j+1] = min(dp[i+1][j+1], dp[i][j]+cost);
            }
        }
    }
    cout << dp[N][M] << endl;

}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}