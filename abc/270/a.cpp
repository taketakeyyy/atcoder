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

void f(ll A, vector<ll> &takahashi) {
    if (A==0) {
        ;
    }
    else if (A==1) {
        takahashi[0] = 1;
    }
    else if (A==2) {
        takahashi[1] = 1;
    }
    else if (A==3) {
        takahashi[0] = 1;
        takahashi[1] = 1;
    }
    else if (A==4) {
        takahashi[2] = 1;
    }
    else if (A==5) {
        takahashi[0] = 1;
        takahashi[2] = 1;
    }
    else if (A==6) {
        takahashi[1] = 1;
        takahashi[2] = 1;
    }
    else {
        takahashi[0] = 1;
        takahashi[1] = 1;
        takahashi[2] = 1;
    }
}

void solve() {
    ll A, B; cin >> A >> B;
    vector<ll> point = {1,2,4};
    vector<ll> takahashi(3), aoki(3);
    f(A, takahashi);
    f(B, aoki);

    ll ans = 0;
    for(ll i=0; i<3; i++) {
        if (takahashi[i]==1 || aoki[i]==1) {
            ans += point[i];
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}