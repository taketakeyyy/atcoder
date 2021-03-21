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
    // 2^20 ≒ 10^6
    ll N, M; cin >> N >> M;
    vector<string> S(N);
    for(int i=0; i<N; i++) {
        cin >> S[i];
    }

    ll ans = 0;

    if (M==1) {
        for(int i=0; i<N; i++) {
            for (int j=i+1; j<N; j++) {
                if (S[i][0]!=S[j][0]) ans++;
            }
        }

        cout << ans << endl;
        return;
    }

    ll odd = 0;  // 解答が1の数が奇数
    ll even = 0; // 解答が1の数が偶数
    for(int i=0; i<N; i++) {
        ll cnt = 0;
        for(int j=0; j<M; j++) {
            if (S[i][j]=='1') cnt++;
        }
        if (cnt%2==0) even++;
        else odd++;
    }

    cout << odd*even << endl;
}


int main() {
    solve();
    return 0;
}