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
        if (x1-1<0 and y1-1<0) return mR[y2][x2];
        else if (x1-1<0) return mR[y2][x2] - mR[y1-1][x2];
        else if (y1-1<0) return mR[y2][x2] - mR[y2][x1-1];
        return mR[y2][x2] - mR[y2][x1-1] - mR[y1-1][x2] + mR[y1-1][x1-1];
    }
};

void solve() {
    ll A, B, C, D; cin >> A >> B >> C >> D;

    {// (A,B), (C,D)をすべて第一象限に持ってくる
        ll diffX = C-A;
        ll diffY = D-B;
        A+=1000000000; A%=4;
        B+=1000000000; B%=2;
        C = A + diffX;
        D = B + diffY;
    }

    // 模様X
    vector<vector<ll>> X = {
        {2, 1, 0, 1},
        {1, 2, 1, 0},
    };
    // 2二元累積和
    Ruisekiwa2D ruiX(X);

    // f(C, D) := 左下が(0,0)、右上が(C,D)の長方形領域の黒の面積を返す
    auto f = [&](ll C, ll D) {
        ll res = 0;
        {// Xの個数
            ll cnt = (C/4)*(D/2);
            res += ruiX.query({0,0}, {1,3}) * cnt;
        }
        {//上側の面積
            ll h = D%2;
            if (h != 0) {
                ll cnt = (C/4);
                res += ruiX.query({0,0}, {h-1, 3}) * cnt;
            }
        }
        {//右側の面積
            ll w = C%4;
            if (w != 0) {
                ll cnt = D/2;
                res += ruiX.query({0,0}, {1, w-1}) * cnt;
            }
        }
        {//右上の面積
            ll h = D%2;
            ll w = C%4;
            if (h!=0 and w!=0) {
                res += ruiX.query({0,0}, {h-1,w-1});
            }
        }
        return res;
    };

    // 答え
    ll ans = 0;
    ans += f(C, D);
    ans -= f(C, B);
    ans -= f(A, D);
    ans += f(A, B);
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}