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
    // 文字列xの数字の大小関係
    // * 桁数が大きい方が正義
    // * 桁数が同じ時 ⇒ 前に大きい数字がある
    // 最小コストをmnとすると、作れる最大桁数Kは K=N/mn
    // 桁数Kで、できるだけ前の方に大きい数字がくるように文字列を作る
    ll N; cin >> N;
    vector<ll> C(10);
    ll mn = INF;
    for(ll i=1; i<=9; i++) {
        cin >> C[i];
        mn = min(mn, C[i]);
    }

    ll K = N/mn;  // 桁数の見積もり
    string ans;
    while(K) {  // O(N)
        for(ll i=9; i>=1; i--) {
            if (N-C[i] >= 0 && (N-C[i])/mn == K-1) {
                ans += to_string(i);
                N -= C[i];
                break;
            }
        }
        K--;
    }
    cout << ans << endl;

}


int main() {
    solve();
    return 0;
}