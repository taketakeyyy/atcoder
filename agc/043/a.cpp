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
    ll H, W; cin >> H >> W;
    vector<string>grid(H);
    for (int i=0; i<H; i++) {
        string line; cin >> line;
        grid[i] = line;
    }

    // dp[h][w] := h行w列に辿り着くのに、最小の操作回数
    vector<vector<ll>> dp(H, vector<ll>(W, (ll)INF));
    if (grid[0][0]=='#') dp[0][0] = 1;
    else dp[0][0] = 0;

    for (int h=0; h<H; h++) {
        for (int w=0; w<W; w++) {
            if (h==0 && w==0) continue;
            if (grid[h][w]=='.') {
                // マスが白い場合
                ll tmp1=(ll)INF, tmp2=(ll)INF;
                if (w-1 >= 0) tmp1 = dp[h][w-1];
                if (h-1 >= 0) tmp2 = dp[h-1][w];
                dp[h][w] = min(tmp1, tmp2);
                continue;
            }
            // マスが黒い場合
            ll tmp1=(ll)INF, tmp2=(ll)INF;
            if (h-1>=0) {
                if (grid[h-1][w]=='.') tmp1 = dp[h-1][w]+1;
                else tmp1 = dp[h-1][w];
            }
            if (w-1>=0) {
                if (grid[h][w-1]=='.') tmp2 = dp[h][w-1]+1;
                else tmp2 = dp[h][w-1];
            }
            dp[h][w] = min(dp[h][w], min(tmp1, tmp2));

            for (int nw=w+1; nw<W; nw++) {
                if (grid[h][nw]=='#') {
                    dp[h][nw] = min(dp[h][nw], dp[h][w]);
                }
                else {
                    break;
                }
            }
        }
    }

    // for (int h=0; h<H; h++) {
    //     for (int w=0; w<W; w++) {
    //         cout << dp[h][w] << " ";
    //     }
    //     cout << endl;
    // }
    cout << dp[H-1][W-1] << endl;
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}