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
    ll K; cin >> K;

    if (K <= 9) {
        cout << K << endl;
        return;
    }

    auto f = [&](auto f, ll now_keta, ll max_keta, ll &order, ll &ans) -> bool {
        // 終了条件
        if (now_keta == max_keta) {
            order++;
            if (order == K) {
                // 出力
                cout << ans << endl;
                return true;
            }
            return false;
        }

        // 探索
        ll n = ans%10;
        for(ll i=0; i<n; i++) {
            ans = ans*10 + i;
            bool res = f(f, now_keta+1, max_keta, order, ans);
            if (res) return true;
            ans = ans/10;
        }
        return false;
    };

    ll order = 9;
    for(ll max_keta=2; max_keta<=10; max_keta++) {
        for(ll i=0; i<=9; i++) {
            ll ans = i;
            bool res = f(f, 1, max_keta, order, ans);
            if (res) return;
        }
    }

}


int main() {
    solve();
    return 0;
}