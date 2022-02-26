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

ll N;
bool judge(ll i, ll j, vector<string> &S) {
    ll white;

    // 右
    white = 0;
    if (j+5 < N) {
        for(ll w=0; w<6; w++) {
            if (S[i][j+w] == '.') white++;
        }
        if (white <= 2) return true;
    }

    // 左
    white = 0;
    if (j-5 >= 0) {
        for(ll w=0; w<6; w++) {
            if (S[i][j-w] == '.') white++;
        }
        if (white <= 2) return true;
    }

    // 上
    white = 0;
    if (i-5 >= 0) {
        for(ll h=0; h<6; h++) {
            if (S[i-h][j] == '.') white++;
        }
        if (white <= 2) return true;
    }

    // 下
    white = 0;
    if (i+5 < N) {
        for(ll h=0; h<6; h++) {
            if (S[i+h][j] == '.') white++;
        }
        if (white <= 2) return true;
    }

    // 上左
    white = 0;
    if (i-5>=0 && j-5>=0) {
        for(ll k=0; k<6; k++) {
            if (S[i-k][j-k] == '.') white++;
        }
        if (white <= 2) return true;
    }

    // 上右
    white = 0;
    if (i-5>=0 && j+5<N) {
        for(ll k=0; k<6; k++) {
            if (S[i-k][j+k] == '.') white++;
        }
        if (white <= 2) return true;
    }

    // 下左
    white = 0;
    if (i+5<N && j-5>=0) {
        for(ll k=0; k<6; k++) {
            if (S[i+k][j-k] == '.') white++;
        }
        if (white <= 2) return true;
    }

    // 下右
    white = 0;
    if (i+5<N && j+5<N) {
        for(ll k=0; k<6; k++) {
            if (S[i+k][j+k] == '.') white++;
        }
        if (white <= 2) return true;
    }

    return false;
}

void solve() {
    cin >> N;
    vector<string> S(N);
    for(ll i=0; i<N; i++) {
        cin >> S[i];
    }

    for(ll i=0; i<N; i++) {
        for(ll j=0; j<N; j++) {
            if (judge(i, j, S)) {
                cout << "Yes" << endl;
                return;
            }
        }
    }
    cout << "No" << endl;
}


int main() {
    solve();
    return 0;
}