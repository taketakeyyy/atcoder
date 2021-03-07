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
const long long INF = LONG_LONG_MAX - 1001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve() {
    // 左(i-1)と右(i)のカードを使ってペアを作るとき、左(i-1)のカードをなるべく先に使い切りたい
    // i-1のカードが奇数なら、1枚iのカードとペアを作って、あとはi-1のカードのみでペアを作る
    // これを繰り返す
    ll N; cin >> N;
    map<ll,ll> mp;
    for (int i=0; i<N; i++) {
        cin >> mp[i];
    }

    if (N==1) {
        cout << mp[0]/2 << endl;
        return;
    }

    ll ans = 0;
    ll pre = mp[0];
    for (int i=1; i<N; i++) {
        if (pre&1) {
            if (mp[i]>=1) {
                ans++;
                pre -= 1;
                mp[i] -= 1;
            }
        }
        ans += pre/2;
        pre = mp[i];
    }
    ans += pre/2;
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}