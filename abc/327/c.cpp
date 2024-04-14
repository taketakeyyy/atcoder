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


void solve() {
    vector<vector<ll>> A(9, vector<ll>(9));
    for(ll i=0; i<9; i++) {
        for(ll j=0; j<9; j++) cin >> A[i][j];
    }

    // 各行の検証
    for(ll i=0; i<9; i++) {
        bool is_ok = true;
        vector<bool> C(10, false);
        for(ll j=0; j<9; j++) {
            if (C[A[i][j]]) {
                is_ok = false;
            }
            else {
                C[A[i][j]] = true;
            }
        }
        if (!is_ok) {
            cout << "No" << endl;
            return;
        }
    }

    // 各列の検証
    for(ll j=0; j<9; j++) {
        bool is_ok = true;
        vector<bool> C(10, false);
        for(ll i=0; i<9; i++) {
            if (C[A[i][j]]) {
                is_ok = false;
            }
            else {
                C[A[i][j]] = true;
            }
        }
        if (!is_ok) {
            cout << "No" << endl;
            return;
        }
    }

    // 各3x3の検証
    auto is_valid = [&](ll h1, ll h2, ll w1, ll w2) {
        bool is_ok = true;
        vector<bool> C(10, false);
        for(ll i=h1; i<=h2; i++) {
            for(ll j=w1; j<=w2; j++) {
                if (C[A[i][j]]) {
                    is_ok = false;
                }
                else {
                    C[A[i][j]] = true;
                }
            }
        }
        return is_ok;
    };
    bool is_ok = true;
    is_ok &= is_valid(0,2,0,2);
    is_ok &= is_valid(0,2,3,5);
    is_ok &= is_valid(0,2,6,8);
    is_ok &= is_valid(3,5,0,2);
    is_ok &= is_valid(3,5,3,5);
    is_ok &= is_valid(3,5,6,8);
    is_ok &= is_valid(6,8,0,2);
    is_ok &= is_valid(6,8,3,5);
    is_ok &= is_valid(6,8,6,8);
    if (!is_ok) {
        cout << "No" << endl;
    }
    else {
        cout << "Yes" << endl;
    }
}


int main() {
    solve();
    return 0;
}