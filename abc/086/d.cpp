#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using P = pair<int,int>;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


/* [(x1,y1), (x2,y2)]の範囲の累積和を返す */
int calc(vector<vector<int>> (&r), int x1, int y1, int x2, int y2) {
    return r[x2+1][y2+1] - r[x2+1][y1] - r[x1][y2+1] + r[x1][y1];
}

void solve(){
    int N, K;
    cin >> N >> K;
    int grid[1005][2005];

    for (int i=0; i<N; i++) {
        int x, y;
        char c;
        cin >> x >> y >> c;

        // 全部'B'に変換する
        if (c == 'W') {
            x += K;
        }
        // x,yを[0,2K)の範囲に変換する
        x = x%(2*K);
        y = y%(2*K);
        // [(0,0), (K,2K))の範囲に変換する
        // (変換1) (x+K, y+K) -> (x,y)
        // (変換2) (x+K, y) -> (x, y+K)
        if (x>=K && y>=K) {  // 変換1
            x = x-K;
            y = y-K;
        }
        if (x>=K) {  // 変換2
            x = x-K;
            y = y+K;
        }
        grid[x][y] += 1;  // 希望の位置を+1する
    }

    /* 2次元累積和rを作る */
    vector<vector<int>> r(1005, vector<int>(2005, 0));
    r[1][1] = grid[0][0];
    for (int x=1; x<K; x++) {
        r[x+1][1] = r[x][1] + grid[x][0];
    }
    for (int y=1; y<2*K; y++) {
        r[1][y+1] = r[1][y] + grid[0][y];
    }
    for (int x=1; x<K; x++) {
        for (int y=1; y<2*K; y++) {
            r[x+1][y+1] = r[x+1][y] + r[x][y+1] - r[x][y] + grid[x][y];
        }
    }

    /* 答えを探索する */
    ll ans = 0;
    for (int x=0; x<K; x++) {
        for (int y=0; y<2*K; y++) {
            ll total = 0;
            int x1, x2, x3, x4, x5, x6;
            int y1, y2, y3, y4, y5, y6;

            if (y+K-1 >= 2*K && x+K-1 >= K) {
                /* xとyが境界をまたぐ場合 */
                x1 = x; y1 = y;
                x2 = K-1; y2 = 2*K-1;
                total += calc(r, x1, y1, x2, y2);

                x3 = x; y3 = 0;
                x4 = K-1; y4 = (y+K-1)%(2*K);
                total += calc(r, x3, y3, x4, y4);

                x5 = 0; y5 = y4+1;
                x6 = x1-1; y6 = y1-1;
                total += calc(r, x5, y5, x6, y6);
            }
            else if (y+K-1 >= 2*K) {
                /* yのみが境界をまたぐ場合 */
                x1 = 0; y1 = y;
                x2 = K-1; y2 = 2*K-1;
                total += calc(r, x1, y1, x2, y2);

                x3 = 0; y3 = 0;
                x4 = K-1; y4 = (y+K-1)%(2*K);
                total += calc(r, x3, y3, x4, y4);
            }
            else if (x+K-1 >= K) {
                /* xのみが境界をまたぐとき */
                x1 = x; y1 = y;
                x2 = K-1; y2 = y+K-1;
                total += calc(r, x1, y1, x2, y2);

                if (y2+1 < 2*K) {
                    x3 = 0; y3 = y2+1;
                    x4 = x-1; y4 = 2*K-1;
                    total += calc(r, x3, y3, x4, y4);

                    x5 = 0; y5 = 0;
                    x6 = x-1; y6 = y-1;
                    total += calc(r, x5, y5, x6, y6);
                }
                else {
                    x3 = 0; y3 = y2+1;
                    x4 = x-1; y4 = 2*K-1;
                    total += calc(r, x3, y3, x4, y4);
                }
            }
            else {
                /* xもyもまたがない場合 */
                x1 = x; y1 = y;
                x2 = x+K-1; y2 = y+K-1;
                total += calc(r, x1, y1, x2, y2);
            }
            ans = max(ans, total);
        }
    }
    cout << ans << endl;
}

/**
 * @brief 二次元累積和
 * @example
 * vector<vector<ll>> A // 二次元配列のデータ
 * Ruiseki2D R(A);
 * ll res = R.query({y1,x1},{y2,x2}) // [(y1,x1), (y2,x2)] の長方形の区間和を返す
 */
class Ruiseki2D {
private:
    vector<vector<ll>> mR; // 累積和

public:
    Ruiseki2D(const vector<vector<ll>> &A) {
        ll H = A.size();
        ll W = A[0].size();
        mR = A;
        // 横方向に累積和
        for(ll i=0; i<H; i++) {
            for(ll j=1; j<W; j++) mR[i][j] += mR[i][j-1];
        }
        // 縦方向に累積和
        for(ll j=0; j<W; j++) {
            for(ll i=1; i<H; i++) mR[i][j] += mR[i-1][j];
        }
    }

    // [(y1,x1), (y2,x2)] の長方形の区間和を返す
    ll query(const pair<ll,ll> &p1, const pair<ll,ll> &p2) {
        ll y1 = p1.first; ll x1 = p1.second;
        ll y2 = p2.first; ll x2 = p2.second;
        if (x1-1<0 and y1-1<0) return mR[y2][x2];
        else if (x1-1<0) return mR[y2][x2] - mR[y1-1][x2];
        else if (y1-1<0) return mR[y2][x2] - mR[y2][x1-1];
        return mR[y2][x2] - mR[y2][x1-1] - mR[y1-1][x2] + mR[y1-1][x1-1];
    }
};

// 解説AC　4つ結合して累積和の条件分岐をなくして簡単に計算できるバージョン
void solve2() {
    ll N, K; cin >> N >> K;
    vector A(2*K, vector(2*K, 0LL)); // A[i][j] := マス(i,j)の希望の個数
    for(ll i=0; i<N; i++) {
        ll x, y; char c; cin >> x >> y >> c;
        if (c=='W') x += K; // 白を黒に変換

        // 2K周期なのでmod 2Kする
        x%=2*K; y%=2*K;
        A[y][x]++;
    }

    // Aを4つ結合してつまり4K*4Kの盤面を作る。累積和が簡単になる
    vector A4(4*K, vector(4*K, 0LL)); // Aを4個つなげたもの
    for(ll i=0; i<4*K; i++) {
        for(ll j=0; j<4*K; j++) A4[i][j] = A[i%(2*K)][j%(2*K)];
    }
    A.clear();// MLE対策

    // 二次元累積和を作る
    Ruiseki2D R(A4);

    // 同時に叶えられる希望の個数の最大値を探す
    ll ans = 0;
    for(ll x=0; x<2*K; x++) {
        for(ll y=0; y<2*K; y++) {
            ll total = R.query({y,x}, {y+K-1, x+K-1}) + R.query({y+K, x+K}, {y+2*K-1, x+2*K-1});
            chmax(ans, total);
        }
    }
    cout << ans << endl;
}


int main(int argc, char const *argv[]){
    // solve();
    solve2();
    return 0;
}