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
    ll Q; cin >> Q;

    ll total = 0;
    priority_queue<ll, vector<ll>, greater<ll>> pq;
    for(ll q=0; q<Q; q++) {
        ll command; cin >> command;
        if (command == 1) {
            ll x; cin >> x;
            pq.push(x-total);
        }
        else if (command == 2) {
            ll x; cin >> x;
            total += x;
        }
        else {
            ll a = pq.top();
            cout << a+total << endl;
            pq.pop();
        }
    }
}


int main() {
    solve();
    return 0;
}