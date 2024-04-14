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
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


// 解説AC
void solve() {
    ll N; cin >> N;
    vector<ll> e(N+1);
    for(ll i=2; i<N+1; i++) {
        ll n = i;
        for(ll j=2; j<i+1; j++) {
            while(n%j == 0) {
                e[j] += 1;
                n /= j;
            }
        }
    }

    // eの要素のうち m-1 以上のものの個数
    auto f = [&](ll m) {
        ll cnt = 0;
        for(ll x: e) {
            if (x >= m-1) cnt++;
        }
        return cnt;
    };

    ll ans = f(75) + f(25)*(f(3)-1) + f(15)*(f(5)-1) + f(5)*(f(5)-1) * (f(3)-2)/2;
    cout << ans << endl;
}

// 解説AC
void solve2() {
    ll N; cin >> N;

    // e[p] := N!のpの指数部の数
    vector<ll> e(N+1);
    // 1からNまでそれぞれ素因数分解して、eを作る
    for(ll i=2; i<=N; i++) {
        ll n = i;
        for(ll j=2; j<=i; j++) {
            while(n%j == 0) {
                e[j]++;
                n /= j;
            }
        }
    }

    ll ans = 0;
    // 1*75のパターン
    for(ll a=2; a<=N; a++) {
        if (e[a]>=74) ans++;
    }
    // 3*25のパターン
    for(ll a=2; a<=N; a++) {
        for(ll b=2; b<=N; b++) {
            if (a == b) continue;
            if (e[a]>=2 && e[b]>=24) ans++;
        }
    }
    // 5*15のパターン
    for(ll a=2; a<=N; a++) {
        for(ll b=2; b<=N; b++) {
            if (a == b) continue;
            if (e[a]>=4 && e[b]>=14) ans++;
        }
    }
    // 3*5*5のパターン
    for(ll a=2; a<=N; a++) {
        for(ll b=2; b<=N; b++) {
            if (a == b) continue;
            for(ll c=b+1; c<=N; c++) {
                if (a == c) continue;
                if (e[a]>=2 && e[b]>=4 && e[c]>=4) ans++;
            }
        }
    }
    cout << ans << endl;
}


int main() {
    // solve();
    solve2();
    return 0;
}