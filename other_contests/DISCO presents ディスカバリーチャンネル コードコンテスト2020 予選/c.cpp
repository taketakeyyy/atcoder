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
    ll H, W, K; cin >> H >> W >> K;
    vector<string> grid(H);
    rep(i,H) {
        cin >> grid[i];
    }
    vector<vector<ll>> ans_grid(H, vector<ll>(W, -1));

    auto paint = [&ans_grid](int h, vector<ll> q, ll k) {
        for (auto w: q) {
            ans_grid[h][w] = k;
        }
    };

    // 各行について、横方向に塗っていく
    ll k = 1;  // 塗る色
    for (int h=0; h<H; h++) {
        vector<ll> que;
        ll cnt = 0;
        for (int w=0; w<W; w++) {
            if (grid[h][w] == '.') {
                que.push_back(w);
            }
            else {
                cnt++;
                if (cnt>=2) {
                    // 新しい長方形にする
                    paint(h, que, k);  // 今までのを塗る
                    k++;
                    que = {};
                    que.push_back(w);
                }
                else {
                    que.push_back(w);
                }
            }
        }
        if (cnt >= 1) {
            paint(h, que, k);
            k++;
        }
    }

    // 一番上の行がまだ塗られてないパターンを考える
    int hh;
    if (ans_grid[0][0]==-1) {
        for (hh=1; hh<H; hh++) {
            if (ans_grid[hh][0]==-1) continue;
            // 塗っていく
            for (int j=0; j<W; j++) {
                for (int i=0; i<hh; i++) {
                    ans_grid[i][j] = ans_grid[hh][j];
                }
            }
            hh++;
            break;
        }
    }
    else {
        hh=0;
    }

    // まだ塗られていないところは、上下を見て長方形になるように塗っていく
    for (int h=hh; h<H; h++) {
        if (ans_grid[h][0] != -1) continue;
        if (h-1 >= 0) {
            // 上に合わせて塗っていく
            for (int w=0; w<W; w++) {
                ans_grid[h][w] = ans_grid[h-1][w];
            }
        }
        else {
            // 下に合わせて塗っていく
            for (int w=0; w<W; w++) {
                ans_grid[h][w] = ans_grid[h+1][w];
            }
        }
    }

    // 出力
    rep(i, H) {
        rep(j, W) {
            cout << ans_grid[i][j];
            if (j!=W-1) cout << " ";
        }
        cout << endl;
    }
}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}