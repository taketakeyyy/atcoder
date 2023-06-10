#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll N; cin >> N;
    ll ans;
    if (N%5 == 0) {
        ans = N;
    }
    else {
        ll n1 = N;
        ll cnt1 = 0;
        while(n1%5!=0) {
            n1++;
            cnt1++;
        }

        ll n2 = N;
        ll cnt2 = 0;
        while(n2%5!=0) {
            n2--;
            cnt2++;
        }

        if (cnt1 < cnt2) {
            ans = n1;
        }
        else {
            ans = n2;
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}