#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
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

// AC
// 二分探索解法O(Nlog(N*max(L)))
void solve1() {
    ll N, M; cin >> N >> M;
    vector<ll> L(N);
    for(ll i=0; i<N; i++) cin >> L[i];

    // 横幅を二分探索する
    auto f = [&](ll x) -> bool{
        ll w = 0; // 横幅
        ll h = 1; // 行数
        for(ll i=0; i<N; i++) {
            if (L[i] > x) return false; // もっと横幅を大きくしてほしい

            if (w+L[i] <= x) {
                w += L[i] + 1;
            }
            else {
                h++;
                w = L[i] + 1;
            }
        }
        if (h > M) return false; // もっと横幅を大きくしてほしい
        return true; // 横幅を小さくしてほしい
    };

    ll l = 0;
    ll r = 2e15;// 空白分も考慮すること！
    while(r-l != 1) {
        ll mid = (l+r)/2;
        if (f(mid)) r = mid;
        else l = mid;
    }
    if (f(l)) {cout << l << endl;}
    else {cout << r << endl;}
}

// AC
// 二分探索解法O(Nlog(N*max(L)))
void solve2() {
    ll N, M; cin >> N >> M;
    vector<ll> L(N);
    for(ll i=0; i<N; i++) cin >> L[i];

    // 横幅を二分探索する
    auto f = [&](ll x) -> ll{
        ll w = 0; // 横幅
        ll h = 1; // 行数
        for(ll i=0; i<N; i++) {
            if (L[i] > x) return 1; // もっと横幅を大きくしてほしい

            if (w+L[i] <= x) {
                w += L[i] + 1;
            }
            else {
                h++;
                w = L[i] + 1;
            }
        }
        if (h > M) return 1; // もっと横幅を大きくしてほしい
        if (h < M) return -1; // 横幅を小さくしてほしい
        return 0; // h==Mのとき
    };

    ll l = 0;
    ll r = 2e15; // 空白分も考慮すること！
    while(r-l != 1) {
        ll mid = (l+r)/2;
        ll res = f(mid);
        if (res==1) l = mid; // 横幅を大きくしてほしい
        else if(res==-1) r = mid; // 横幅を小さくしてほしい
        else r = mid; // h==Mのとき、できるだけ横幅を小さくしたい
    }
    if (f(l)==0) {cout << l << endl;}
    else {cout << r << endl;}
}


int main() {
    solve1();
    // solve2();
    return 0;
}