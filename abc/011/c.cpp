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
istream& operator>>(istream& is, mint& a) { return is >> a.x;}
ostream& operator<<(ostream& os, const mint& a) { return os << a.x;}


void solve(){
    ll N; cin >> N;
    vector<ll>NG(3);
    rep(i,3) {
        cin >> NG[i];
        if (NG[i]==N) {
            cout << "NO" << endl;
            return;
        }
    }

    vector<ll> dp(N+1, LONG_LONG_MAX-100);  // dp[i] := 数字iに到達するのに必要な最小手数
    dp[N] = 0;
    for (int i=N; i>=1; i--) {
        bool is_ng = false;
        for (int k=0; k<3; k++) {
            if (NG[k]==i) {
                is_ng = true;
                break;
            }
        }
        if (is_ng) continue;

        for (int j=1; j<=3; j++) {
            if (!(i-j >= 0)) break;

            bool flag = false;
            for (int k=0; k<3; k++) {
                if (dp[i-j]==NG[k]) {
                    flag = true;
                    break;
                }
            }
            if (flag) continue;
            dp[i-j] = min(dp[i-j], dp[i]+1);
        }
    }

    if (dp[0] <= 100) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }

    return;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}