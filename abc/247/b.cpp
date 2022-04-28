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
    vector<string> t(N), s(N);
    map<string, ll> mp;
    for(ll i=0; i<N; i++) {
        cin >> s[i] >> t[i];
        if (s[i] != t[i]) {
            mp[s[i]]++;
            mp[t[i]]++;
        }
        else {
            mp[s[i]]++;
        }
    }

    for(ll i=0; i<N; i++) {
        if (mp[s[i]] >= 2 && mp[t[i]] >= 2) {
            cout << "No" << endl;
            return;
        }
    }
    cout << "Yes" << endl;
}


int main() {
    solve();
    return 0;
}