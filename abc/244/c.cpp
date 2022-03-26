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
    set<ll> used;

    ll takahashi = 1;

    while (1) {
        // 高橋の手番
        while(1) {
            if (used.count(takahashi)) {
                takahashi++;
                continue;
            }
            break;
        }
        cout << takahashi << endl;
        flush(cout);
        used.insert(takahashi);
        takahashi++;

        // 青木の手番
        ll aoki;
        cin >> aoki;
        if (aoki == 0) {
            return;
        }
        used.insert(aoki);
    }
}


int main() {
    solve();
    return 0;
}