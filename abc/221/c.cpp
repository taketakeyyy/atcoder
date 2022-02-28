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
    string N; cin >> N;
    sort(N.begin(), N.end());

    ll ans = 0;
    do {  // 高々9!(=362880)
        for(ll i=1; i<N.size(); i++) {  // 高々8
            string s1 = N.substr(0,i);
            string s2 = N.substr(i,N.size()-i);
            if (s1.size()==0 || s2.size()==0) continue;
            if (s1[0]=='0' || s2[0]=='0') continue;
            ll n1 = stoll(s1);
            ll n2 = stoll(s2);
            ans = max(ans, n1*n2);
        }
    }while (next_permutation(N.begin(), N.end()));

    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}