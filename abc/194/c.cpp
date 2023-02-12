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


// WA
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

// AC
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

// AC
// A[i]の取りうる値の範囲が [-200, 200] の 401通りしかないので、
// 各A[i]の出現回数cntAを数える
// するとある組(a1,a2) が (a1-a2)^2 で計算される回数は、cntA[a1]*cntA[a2] 回。
// (a1,a2)の組を2重ループで探索すればOK
void solve3() {
    ll N; cin >> N;
    map<ll,ll> cntA;
    for (int i=0; i<N; i++) {
        ll a; cin >> a;
        cntA[a]++;
    }

    ll ans = 0;
    for(ll a1=-200; a1<=200; a1++) {
        for(ll a2=a1+1; a2<=200; a2++) {
            ans += cntA[a1]*cntA[a2]*(a1-a2)*(a1-a2);
        }
    }
    cout << ans << endl;
}

int main() {
    // solve();
    // solve2();
    solve3();
    return 0;
}