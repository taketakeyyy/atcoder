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
    ll N, K; cin >> N >> K;
    string S; cin >> S;
    if (N==1) {
        cout << 0 << endl;
        return;
    }

    // ランレングス圧縮して、真中部分をどんどん入れ替えればよい
    // 1個入れ替えるごとに幸福度は2増える
    // ただし端っこは1しか増えない
    ll ans = 0;
    for(int i=0; i<N-1; i++) {
        if (S[i]==S[i+1]) ans++;
    }
    ans = min(ans+2*K, N-1);
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}