#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
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
    ll N, P, Q; cin >> N >> P >> Q;
    vector<ll> A(N);
    for(int i=0; i<N; i++) cin >> A[i];

    ll ans = 0;
    for(int i=0; i<N; i++) {
        for(int j=i+1; j<N; j++) {
            for(int k=j+1; k<N; k++) {
                for(int l=k+1; l<N; l++) {
                    for(int m=l+1; m<N; m++) {
                        ll result = A[i]%P;
                        result *=A[j]; result%=P;
                        result *=A[k]; result%=P;
                        result *=A[l]; result%=P;
                        result *=A[m]; result%=P;
                        if (result == Q) ans++;
                    }
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