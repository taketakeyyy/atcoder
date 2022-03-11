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
    ll L, Q; cin >> L >> Q;
    // multiset<ll> ms;
    set<ll> ms;  // setもlower_bound使える
    for(ll q=0; q<Q; q++) {
        ll c, x; cin >> c >> x;
        if (c == 1) {
            // 切る
            ms.insert(x);
        }
        else {
            // 出力
            if (ms.empty()) {
                cout << L << endl;
                continue;
            }

            auto it = ms.lower_bound(x);
            if (it == ms.begin()) {
                cout << (*it) << endl;
            }
            else if (it == ms.end()) {
                it--;
                cout << L - (*it) << endl;
            }
            else {
                ll a = (*it);
                ll b = *(--it);
                cout << a - b << endl;
            }
        }
    }

}


int main() {
    solve();
    return 0;
}