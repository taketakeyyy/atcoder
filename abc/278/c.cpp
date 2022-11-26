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
    ll N, Q; cin >> N >> Q;
    map<ll,set<ll>> follow;

    for(ll q=0; q<Q; q++) {
        ll t, a, b;
        cin >> t >> a >> b;
        if (t == 1) {
            // a が bをフォローする
            follow[a].insert(b);
        }
        else if (t == 2) {
            // aがbをフォロー解除
            follow[a].erase(b);
        }
        else if (t == 3) {
            if (follow[a].count(b) && follow[b].count(a)) {
                cout <<  "Yes" << endl;
            }
            else {
                cout << "No" << endl;
            }
        }
    }
}


int main() {
    solve();
    return 0;
}