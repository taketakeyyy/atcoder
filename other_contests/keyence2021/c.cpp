#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 998244353
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
    /* 本番WA */
    int H, W, K;
    cin >> H >> W >> K;
    vector<vector<char>> grid(H+1, vector<char>(W+1, ' '));
    for (int i=0; i<K; i++) {
        int h, w;
        char c;
        cin >> h >> w >> c;
        grid[h][w] = c;
    }

    // dp[h][w] := h行w列にいるときの移動経路の総和
    vector<vector<int>> dp(H+1, vector<int>(W+1, 0));
    dp[1][1] = 1;
    for (int w=2; w<W+1; w++) {
        if (grid[1][w-1] == ' ') {
            dp[1][w] = (dp[1][w-1]*2)%MOD;
        }
        else if (grid[1][w-1] == 'X' || grid[1][w-1] == 'R') {
            dp[1][w] = dp[1][w-1];
        }
        else {
            dp[1][w] = 0;
        }
    }
    for (int h=2; h<H+1; h++) {
        if (grid[h-1][1] == ' ') {
            dp[h][1] = (dp[h-1][1]*2)%MOD;
        }
        else if (grid[h-1][1] == 'X' || grid[h-1][1] == 'D') {
            dp[h][1] = dp[h-1][1];
        }
        else {
            dp[h][1] = 0;
        }
    }

    for (int h=2; h<H+1; h++) {
        for (int w=2; w<W+1; w++) {
            // 上空白、左空白
            if (grid[h-1][w] == ' ' && grid[h][w-1] == ' ') {
                dp[h][w] = ((dp[h-1][w]*6)%MOD + (dp[h][w-1]*6)%MOD)%MOD;
            }

            // 上が空白、左から移動可能のとき
            else if ((grid[h-1][w]==' ' && grid[h][w-1]=='X') ||
                     (grid[h-1][w]==' ' && grid[h][w-1]=='R')
                    ) {
                dp[h][w] = ((dp[h-1][w]*2)%MOD + (dp[h][w-1]*3)%MOD);
            }
            // 上が空白、左から移動不可能のとき
            else if ((grid[h-1][w]==' ' && grid[h][w-1]=='D')) {
                dp[h][w] = (dp[h-1][w]*2)%MOD;
            }

            // 上から移動可能、左が空白のとき
            else if ((grid[h-1][w]=='X' && grid[h][w-1]==' ') ||
                     (grid[h-1][w]=='D' && grid[h][w-1]==' ')
                    ) {
                dp[h][w] = ((dp[h-1][w]*3)%MOD + (dp[h][w-1]*2)%MOD)%MOD;
            }
            // 上から移動不可能、左が空白のとき
            else if ((grid[h-1][w]=='R' && grid[h][w-1]==' ')) {
                dp[h][w] = (dp[h][w-1]*2)%MOD;
            }

            // 以降は、上と左に文字が予め書いてあるときの場合分け
            else if ((grid[h-1][w]=='R' && grid[h][w-1]=='R')) {
                dp[h][w] = dp[h][w-1];
            }
            else if ((grid[h-1][w]=='R' && grid[h][w-1]=='D')) {
                dp[h][w] = 0;
            }
            else if ((grid[h-1][w]=='R' && grid[h][w-1]=='X')) {
                dp[h][w] = dp[h][w-1];
            }

            else if ((grid[h-1][w]=='D' && grid[h][w-1]=='R')) {
                dp[h][w] = (dp[h-1][w] + dp[h][w-1])%MOD;
            }
            else if ((grid[h-1][w]=='D' && grid[h][w-1]=='D')) {
                dp[h][w] = dp[h-1][w];
            }
            else if ((grid[h-1][w]=='D' && grid[h][w-1]=='X')) {
                dp[h][w] = (dp[h-1][w] + dp[h][w-1])%MOD;
            }

            else if ((grid[h-1][w]=='X' && grid[h][w-1]=='R')) {
                dp[h][w] = (dp[h-1][w] + dp[h][w-1])%MOD;
            }
            else if ((grid[h-1][w]=='X' && grid[h][w-1]=='D')) {
                dp[h][w] = dp[h-1][w];
            }
            else if ((grid[h-1][w]=='X' && grid[h][w-1]=='X')) {
                dp[h][w] = (dp[h-1][w] + dp[h][w-1])%MOD;
            }
        }
    }

    // for (int h=1; h<H+1; h++) {
    //     for (int w=1; w<W+1; w++) {
    //         cout << dp[h][w] << " ";
    //     }
    //     cout << endl;
    // }

    cout << dp[H][W] << endl;
}


void solve2(){
    /* 解説AC */
    int H, W, K;
    cin >> H >> W >> K;
    vector<vector<char>> grid(H+1, vector<char>(W+1, ' '));
    for (int i=0; i<K; i++) {
        int h, w;
        char c;
        cin >> h >> w >> c;
        grid[h][w] = c;
    }
    // modintの「3で割る」は、「3の逆元をかける」に等しい
    // inv()の計算は重いので、予め計算しておく
    mint inv3 = mint(3).inv();

    // dp[h][w] := h行w列にいるときの移動経路の総和
    vector<vector<mint>> dp(H+1, vector<mint>(W+1, 0));
    dp[1][1] = 1;
    for (int h=2; h<H+1; h++) {
        if (grid[h-1][1]=='X' || grid[h-1][1]=='D') {
            dp[h][1] = dp[h-1][1];
        }
        else if (grid[h-1][1]==' ') {
            dp[h][1] = (dp[h-1][1]*2)*inv3;
            // dp[h][1] = dp[h-1][1]*2/3;  // 「3で割る」という行為は重いので、inv3をかける方法に変更
        }
    }
    for (int w=2; w<W+1; w++) {
        if (grid[1][w-1]=='X'||grid[1][w-1]=='R') {
            dp[1][w] = dp[1][w-1];
        }
        else if (grid[1][w-1]==' ') {
            dp[1][w] = (dp[1][w-1]*2)*inv3;
            // dp[1][w] = dp[1][w-1]*2/3;
        }
    }

    for (int h=2; h<H+1; h++) {
        for (int w=2; w<W+1; w++) {
            // 上から
            if (grid[h-1][w]==' ') {
                dp[h][w] += dp[h-1][w]*2*inv3;
                // dp[h][w] += dp[h-1][w]*2/3;
            }
            else if (grid[h-1][w]=='X'||grid[h-1][w]=='D') {
                dp[h][w] += dp[h-1][w];
            }

            // 左から
            if (grid[h][w-1]==' ') {
                dp[h][w] += dp[h][w-1]*2*inv3;
                // dp[h][w] += dp[h][w-1]*2/3;
            }
            else if (grid[h][w-1]=='X'||grid[h][w-1]=='R') {
                dp[h][w] += dp[h][w-1];
            }
        }
    }

    mint ans = mint(3).pow(H*W-K) * dp[H][W];
    cout << ans.x << endl;
}


int main(int argc, char const *argv[]){
    solve2();
    return 0;
}