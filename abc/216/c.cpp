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
    const ll MAX_COUNT = 120;

    // 逆から考える。Nから、ひたすら1/2していき、最後に魔法Aで一つ消す。空になったらOK
    vector<char> ans;
    if (N%2 == 1) {
        ans.push_back('A');
        N--;
    }

    while(N!=0) {
        if (N%2 == 0) {
            ans.push_back('B');
            N /= 2;
        }
        else {
            ans.push_back('A');
            N--;
        }
    }

    // 逆から出力
    for(ll i=ans.size()-1; i>=0; i--) {
        cout << ans[i];
    }
    cout << endl;
}


int main() {
    solve();
    return 0;
}