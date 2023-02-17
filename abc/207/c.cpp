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


void solve() {
    ll N; cin >> N;
    vector<tuple<ll,double,double>> kukan(N);
    for(ll i=0; i<N; i++) {
        ll t;
        double l, r;
        cin >> t >> l >> r;
        kukan[i] = {t, l, r};
    }

    ll ans = 0;
    for(ll i=0; i<N; i++) {
        auto[t1, l1, r1] = kukan[i];
        // 閉区間になおす
        if (t1 == 2) r1 -= 0.5;
        if (t1 == 3) l1 += 0.5;
        if (t1 == 4) {r1-=0.5; l1+=0.5;}

        for(ll j=i+1; j<N; j++) {
            auto[t2, l2, r2] = kukan[j];
            // 閉区間になおす
            if (t2 == 2) r2 -= 0.5;
            if (t2 == 3) l2 += 0.5;
            if (t2 == 4) {r2-=0.5; l2+=0.5;}

            // if (max(l1,l2) <= min(r1,r2)) ans++;
            if ((l1<=l2&&l2<=r1) || (l2<=l1&&l1<=r2)) ans++;
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}