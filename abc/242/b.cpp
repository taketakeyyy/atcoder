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
    string S; cin >> S;
    map<int,int>mp;
    for(ll i=0; i<S.size(); i++) {
        mp[S[i]] += 1;
    }

    int start = 'a';
    int finish = 'z';
    // string ans = "";
    for(ll i=start; i<=finish; i++) {
        while(mp[i]!=0) {
            mp[i]--;
            cout << char(i);
        }
    }
    cout << endl;
}


int main() {
    solve();
    return 0;
}