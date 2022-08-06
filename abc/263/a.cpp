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
    ll A, B, C, D, E; cin >> A >> B >> C >> D >> E;
    map<ll,ll> mp;
    mp[A]++;
    mp[B]++;
    mp[C]++;
    mp[D]++;
    mp[E]++;

    bool exist_3 = false, exist_2 = false;
    for(auto[key, val]: mp) {
        if (val == 3) {
            exist_3 = true;
        }
        if (val == 2) {
            exist_2 = true;
        }
    }

    if (exist_2 && exist_3) {
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