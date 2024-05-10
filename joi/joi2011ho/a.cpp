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
    ll M, N; cin >> M >> N;
    ll K; cin >> K;
    vector J(M, vector(N, 0LL));
    vector O(M, vector(N, 0LL));
    vector I(M, vector(N, 0LL));
    for(ll i=0; i<M; i++) {
        for(ll j=0; j<N; j++) {
            char c; cin >> c;
            if (c=='J') J[i][j] = 1;
            if (c=='O') O[i][j] = 1;
            if (c=='I') I[i][j] = 1;
        }
    }

    // 二次元累積和
    Ruisekiwa2D RJ(J);
    Ruisekiwa2D RO(O);
    Ruisekiwa2D RI(I);

    // クエリ処理
    for(ll k=0; k<K; k++) {
        ll a, b, c, d; cin >> a >> b >> c >> d;
        a--; b--; c--; d--;
        cout << RJ.query({a,b}, {c,d}) << " ";
        cout << RO.query({a,b}, {c,d}) << " ";
        cout << RI.query({a,b}, {c,d}) << endl;
    }
}


int main() {
    solve();
    return 0;
}