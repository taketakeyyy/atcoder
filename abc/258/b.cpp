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
    vector<string> A(N);
    for(ll i=0; i<N; i++) {
        cin >> A[i];
    }

    // 方向は最初にだけ決めれることに注意（毎回方向を決めれるわけではない）
    ll ans = 0;
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<N; j++) {
            for(ll dx=-1; dx<=1; dx++) {
                for(ll dy=-1; dy<=1; dy++) {
                    if (dx==0 && dy==0) continue;
                    ll a = A[i][j]-'0';
                    ll ni = (i+dx+N)%N;
                    ll nj = (j+dy+N)%N;
                    for(ll n=1; n<=N-1; n++) {
                        a = a*10+(A[ni][nj]-'0');
                        ni = (ni+dx+N)%N;
                        nj = (nj+dy+N)%N;
                    }
                    ans = max(ans, a);
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