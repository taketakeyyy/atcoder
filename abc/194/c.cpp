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
    ll N; cin >> N;
    vector<ll> A(N);
    for (int i=0; i<N; i++) {
        cin >> A[i];
    }
    const long long maxA = 200;
    vector<ll> D(maxA*2+1);  // a=[-200,200], D[a]:= A[i]=aとなるA[i]の個数
    ll ans = 0;
    for(int i=0; i<N; i++) {
        for(int aj=-maxA; aj<=maxA; aj++) {
            ll c = D[maxA+aj];
            ll x = A[i]-aj;
            ans += x*x*c;
        }
        D[maxA+A[i]]++;
    }
    cout << ans << endl;
}

void solve2() {
    ll N; cin >> N;
    vector<ll> A(N);
    for (int i=0; i<N; i++) {
        cin >> A[i];
    }
    const long long maxA = 200;
    // cnt[a] := Aにaが何個出現するか
    // cnt[i]*cnt[j]*(i-j)^2 を求める
    vector<ll>cnt(maxA*2+1, 0);
    for(int i=0; i<N; i++) {
        cnt[maxA+A[i]]++;
    }

    ll ans = 0;
    for(int i=-maxA; i<=maxA; i++) {
        for (int j=i+1; j<=maxA; j++) {
            ans += cnt[maxA+i]*cnt[maxA+j]*(i-j)*(i-j);
        }
    }
    cout << ans << endl;
}

int main() {
    // solve();
    solve2();
    return 0;
}