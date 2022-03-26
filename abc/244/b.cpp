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
    ll N; cin >> N;
    string T; cin >> T;
    ll dir = 0;  // direction
    ll x=0, y=0;

    for(ll i=0; i<T.size(); i++) {
        if (T[i] == 'S') {
            if (dir == 0) {
                x++;
            }
            else if (dir == 1) {
                y--;
            }
            else if (dir == 2) {
                x--;
            }
            else {
                y++;
            }
        }
        else {
            dir += 1;
            dir %= 4;
        }
    }

    cout << x << " " << y << endl;
}


int main() {
    solve();
    return 0;
}