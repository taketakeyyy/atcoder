#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) (a+(b-1))/b
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve() {
    ll N; cin >> N;
    ll A, B, C; cin >> A >> B >> C;

    // 順番に何枚使うか、全探索
    ll LIMIT = 9999;
    ll ans = LIMIT;
    for(ll a=0; a<=LIMIT; a++) {
        if (A*a > N) break;
        for(ll b=0; a+b<=LIMIT; b++) {
            if (A*a+B*b > N) break;
            if ((N-(A*a+B*b))%C==0) {
                ans = min(ans, a+b+(N-(A*a+B*b))/C);
            }
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}