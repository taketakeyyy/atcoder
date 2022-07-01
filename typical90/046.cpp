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
    ll N; cin >> N;
    map<ll,ll> Amp, Bmp, Cmp;  // 頻度
    for(ll i=0; i<N; i++) {
        ll a; cin >> a;
        a %= 46;
        Amp[a]++;
    }
    for(ll i=0; i<N; i++) {
        ll a; cin >> a;
        a %= 46;
        Bmp[a]++;
    }
    for(ll i=0; i<N; i++) {
        ll a; cin >> a;
        a %= 46;
        Cmp[a]++;
    }

    // たかだか46*46*46のステップ数
    ll ans = 0;
    for(auto[ak, av]: Amp) {
        for(auto[bk, bv]: Bmp) {
            for(auto[ck, cv]: Cmp) {
                if ((ak + bk + ck)%46 == 0) {
                    ans += av * bv * cv;
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