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
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll N, M; cin >> N >> M;
    string S, T; cin >> S >> T;
    bool is_head = true;
    for(ll i=0; i<N; i++) {
        if (S[i]==T[i]) continue;
        is_head = false;
        break;
    }

    bool is_tail = true;
    ll j = 0;
    for(ll i=M-N; i<M; i++) {
        if (S[j]==T[i]) {
            j++; continue;
        }
        is_tail = false;
        break;
    }

    if (is_head && is_tail) {
        cout << 0 << endl;
    }
    else if (is_head && !is_tail) {
        cout << 1 << endl;
    }
    else if (!is_head && is_tail) {
        cout << 2 << endl;
    }
    else {
        cout << 3 << endl;
    }
}


int main() {
    solve();
    return 0;
}