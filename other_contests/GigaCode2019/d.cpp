#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


/**
 * @brief 二次元累積和
 * @example
 * vector<vector<ll>> A // 二次元配列のデータ
 * Ruisekiwa2D R(A);
 * ll res = R.query({y1,x1},{y2,x2}) // [(y1,x1), (y2,x2)] の長方形の区間和を返す
 */
class Ruisekiwa2D {
private:
    vector<vector<ll>> mR; // 累積和

public:
    Ruisekiwa2D(const vector<vector<ll>> &A) {
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
        if (x1-1<0LL and y1-1<0LL) return mR[y2][x2];
        else if (x1-1<0LL) return mR[y2][x2] - mR[y1-1][x2];
        else if (y1-1<0LL) return mR[y2][x2] - mR[y2][x1-1];
        return mR[y2][x2] - mR[y2][x1-1] - mR[y1-1][x2] + mR[y1-1][x1-1];
    }
};

vector<long long> divisor(long long n) {
    /***
     * 正整数nの約数を列挙する
     *
     * Args
     *  n(long long): nの約数を列挙する
     *
     * Return
     *  vector<long long> 約数を格納したvector
     *
     * Note
     *  ソートされていないので注意
     ***/
    vector<long long> ans;
    for (long long i=1LL; i*i<=n; i++) {
        if (n%i==0) {
            ans.push_back(i);
            if (i!=n/i) ans.push_back(n/i);
        }
    }
    return ans;
}

void solve() {
    ll H, W, K, V; cin >> H >> W >> K >> V;
    vector A(H, vector(W, 0LL));
    for(ll i=0; i<H; i++) {
        for(ll j=0; j<W; j++) cin >> A[i][j];
    }

    // 二次元累積和
    Ruisekiwa2D R(A);

    // 面積sの家を買うことができるか？ O(√s + √sHW)
    auto f = [&](ll s) {
        if (s == 0) return true;
        if (s*K > V) return false;

        // sの約数を列挙する
        auto divs = divisor(s);
        sort(divs.begin(), divs.end());
        ll DN = divs.size();

        // (縦の長さh, 横の長さw)の組を全探索
        for(ll i=0; i<DN; i++) {
            ll h = divs[i]; // 縦の長さ
            ll w = divs[DN-1-i]; // 横の長さ

            // 左上の(ly,lx)座標を全探索
            for(ll ly=0; ly<H; ly++) {
                ll ry = ly+h-1; // 右下のy座標
                if (ry >= H) break;
                for(ll lx=0; lx<W; lx++) {
                    ll rx = lx+w-1; // 右下のx座標
                    if (rx >= W) break;
                    ll total = R.query({ly,lx}, {ry,rx}) + s*K;
                    if (total <= V) return true;
                }
            }
        }
        return false;
    };

    // 答えを探す（二分探索はだめ）
    ll ans = 0;
    for(ll s=H*W; s>=0; s--) { // O(HW)
        if (!f(s)) continue;
        ans = s;
        break;
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}