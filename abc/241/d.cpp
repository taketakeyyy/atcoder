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
    // O(Q*log(ms.size()))
    ll Q; cin >> Q;
    multiset<ll> ms;

    for(ll q=0; q<Q; q++) {
        ll command, x, k;
        cin >> command >> x;
        if (command == 1) {
            ms.insert(x);
            continue;
        }

        else if (command == 2) {
            cin >> k;
            k--;
            // x以下の要素のうち、大きい方からk番目を出力
            auto it = ms.upper_bound(x);
            if (it==ms.begin()) {
                cout << -1 << endl;
                continue;
            }
            it--;

            while(it != ms.begin()) {
                if (k == 0) break;
                k--;
                it--;
            }

            if (it==ms.begin() && k!=0) {
                cout << -1 << endl;
                continue;
            }
            cout << (*it) << endl;
            continue;
        }

        else {
            cin >> k;
            k--;
            // x以上の要素のうち、小さい方からk番目を出力
            auto it = ms.lower_bound(x);
            while(it != ms.end()) {
                if (k == 0) break;
                k--;
                it++;
            }

            if (it == ms.end()) {
                cout << -1 << endl;
                continue;
            }
            cout << (*it) << endl;
            continue;
        }
    }
}


int main() {
    solve();
    return 0;
}