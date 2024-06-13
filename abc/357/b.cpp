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
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    string S; cin >> S;

    ll low = 0;
    ll big = 0;
    for(char ch: S) {
        if (islower(ch)) low++;
        else big++;
    }

    if (low > big) {
        transform(S.begin(), S.end(), S.begin(), ::tolower);
    }
    else {
        transform(S.begin(), S.end(), S.begin(), ::toupper);
    }
    cout << S << endl;
}


int main() {
    solve();
    return 0;
}