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
    ll N; cin >> N;

    // 5進数でn番目の数字を返す
    auto f = [&](ll n) {
        vector<ll> A;
        while(n != 0) {
            A.push_back(n%5);
            n /= 5;
        }

        ll res = 0;
        ll pow10 = 1;
        for(ll i=0; i<(ll)A.size(); i++) {
            ll a;
            if (A[i] == 0) a = 0;
            else if (A[i] == 1) a = 2;
            else if (A[i] == 2) a = 4;
            else if (A[i] == 3) a = 6;
            else if (A[i] == 4) a = 8;
            res += a*pow10;
            pow10 *= 10;
        }
        return res;
    };
    cout << f(N-1) << endl;
}


int main() {
    solve();
    return 0;
}