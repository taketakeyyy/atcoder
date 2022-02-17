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


void solve() {
    string S; cin >> S;

    // まず、前と後ろのaの数を数える
    ll front = 0;
    for (ll i=0; i<S.size(); i++) {
        if (S[i] == 'a') {
            front++;
            continue;
        }
        break;
    }
    ll back = 0;
    for (ll i=S.size()-1; i>=0; i--) {
        if (S[i] == 'a') {
            back++;
            continue;
        }
        break;
    }
    if (back < front) {
        cout << "No" << endl;
        return;
    }

    // 回文判定
    ll l = front;
    ll r = S.size()-1-back;
    bool is_ok = true;
    while (l < r) {
        if (S[l] == S[r]) {
            l++; r--;
            continue;
        }
        is_ok = false;
        break;
    }

    if (is_ok) {
        cout << "Yes" << endl;
    }
    else {
        cout << "No" << endl;
    }
}


int main() {
    solve();
    return 0;
}