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
    ll N, M; cin >> N >> M;
    vector<ll> A(N);
    rep(i,N) {
        cin >> A[i];
    }
    // 尺取法
    map<ll,ll> mp;
    ll ans = 0;
    for(int i=0; i<M; i++) {
        mp[A[i]]++;
        if (A[i]==ans) {
            while(1) {
                ans++;
                if (!mp.count(ans) || mp[ans]==0) {
                    break;
                }
            }
        }
    }
    for (int i=1; i<N; i++) {
        if (ans == 0) break;
        if (i+M-1==N) break;

        mp[A[i+M-1]]++;
        mp[A[i-1]]--;
        if (mp[A[i-1]]==0 && A[i-1]<ans) {
            ans = A[i-1];
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}