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
    if (N == 1) {
        cout << 1 << endl;
        return;
    }

    deque<pair<ll,ll>> que; que.push_back({-1,-1});  // dammy
    ll a; cin >> a;
    que.push_back({a,1});
    ll total = 1;
    cout << 1 << endl;
    for(ll i=1; i<N; i++) {
        cin >> a;
        ll pre, seq;
        tie(pre, seq) = que.back();
        total++;

        if (a == pre) {
            seq++;
            if (pre == seq) {
                // 消える
                total -= seq;
                que.pop_back();
            }
            else {
                // 消えない
                que.pop_back();
                que.push_back({a, seq});
            }
        }
        else {
            que.push_back({a, 1});
        }

        cout << total << endl;
    }
}


int main() {
    solve();
    return 0;
}