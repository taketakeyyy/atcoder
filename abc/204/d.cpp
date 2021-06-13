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
    vector<ll> T(N);
    ll total = 0;
    for(int i=0; i<N; i++) {
        cin >> T[i];
        total += T[i];
    }

    set<ll> possibles;  // ありうるオーブン1の使う時間
    possibles.insert(0);
    for(int i=0; i<N; i++) {  // たかだか100
        set<ll> tmp = possibles;
        for(auto t: tmp) {  // たかだか10^5
            possibles.insert(t+T[i]);
        }
    }

    // 答えを探す
    ll ans = INF;
    for(auto t: possibles) {
        ll oven1 = abs(total-t);
        ll oven2 = abs(total-oven1);
        ans = min(ans, max(oven1, oven2));
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}