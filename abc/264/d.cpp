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

    // aを1番目に持ってくる
    // tを2番目に持ってくる
    // cを3番目に...
    // 貪欲的にやればいいのか？
    ll ans = 0;
    string ac = "atcoder";
    ll aci = 0;
    while(S != ac) {
        for(ll i=0; i<S.size(); i++) {
            if (S[i]==ac[aci]) {
                if (i==aci) {
                    aci++;
                    break;
                }
                else {
                    while(i-1 >= aci) {
                        swap(S[i], S[i-1]);
                        ans++;
                        i--;
                    }
                    break;
                }
            }
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}