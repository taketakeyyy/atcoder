#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/b)
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll H, W; cin >> H >> W;
    vector<string> A(H);
    vector<string> B(H);
    for(ll i=0; i<H; i++) cin >> A[i];
    for(ll i=0; i<H; i++) cin >> B[i];

    auto horizon_shift = [&]() {
        auto tmpA = A;
        for(ll i=0; i<H; i++) {
            for(ll j=0; j<W; j++) {
                A[i][(j+1)%W] = tmpA[i][j];
            }
        }
    };

    auto vertical_shift = [&]() {
        auto tmpA = A;
        for(ll i=0; i<H; i++) {
            A[(i+1)%H] = tmpA[i];
        }
    };

    auto is_same = [&]() {
        bool is_ok = true;
        for(ll h=0; h<H; h++) {
            if (A[h]!=B[h]) is_ok = false;
        }
        return is_ok;
    };

    // 全探索
    for(ll i=0; i<H; i++) {
        for(ll j=0; j<W; j++) {
            horizon_shift();
            if (is_same()) {
                cout << "Yes" << endl;
                return;
            }
        }
        vertical_shift();
        if (is_same()) {
            cout << "Yes" << endl;
            return;
        }
    }
    cout << "No" << endl;
}


int main() {
    solve();
    return 0;
}