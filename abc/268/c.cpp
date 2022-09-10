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


void solve() {
    ll N; cin >> N;
    vector<ll> P(N);
    map<ll,ll> p2i;  // 料理pの位置i
    for(ll i=0; i<N; i++) {
        cin >> P[i];
        p2i[P[i]] = i;
    }

    // happy[i] := i回回転したときに喜ぶ人数
    vector<ll> happy(N, 0);
    for(ll i=0; i<N; i++) {
        // 人iは、何回転したときに喜ぶか？
        ll j;
        if (p2i[i] < i) {
            j = i - p2i[i];
        }
        else {
            j = N - p2i[i] + i;
        }
        ll nj1 = j;  // j回転
        ll nj2 = (j+1)%N;  // j+1回転
        ll nj3;  // j-1回転
        if (j-1 < 0) { nj3 = j-1+N; }  // C++ならでは
        else { nj3 = (j-1)%N; }
        happy[nj1]++;
        happy[nj2]++;
        happy[nj3]++;
    }

    ll ans = 0;
    for(ll i=0; i<N; i++) {
        ans = max(ans, happy[i]);
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}