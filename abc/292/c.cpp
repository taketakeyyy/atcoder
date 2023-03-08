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
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };

/***
 * 正整数nの約数を列挙する
 *
 * Args
 *  n(long long): nの約数を列挙する
 *
 * Return
 *  vector<long long> 約数を格納したvector
 *
 * Note
 *  ソートされていないので注意
 ***/
vector<long long> divisor(long long n) {
    vector<long long> ans;
    for (long long i=1LL; i*i<=n; i++) {
        if (n%i==0) {
            ans.push_back(i);
            if (i!=n/i) ans.push_back(n/i);
        }
    }
    return ans;
}

void solve() {
    ll N; cin >> N;
    ll ans = 0;
    for(ll ab=1; ab<=N/2; ab++) {
        ll cd = N-ab;

        if (ab != cd) {
            auto divab = divisor(ab);
            auto divcd = divisor(cd);
            ans += (divab.size() * divcd.size())*2;
        }
        else {
            auto divab = divisor(ab);
            ans += (divab.size() * divab.size());
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}