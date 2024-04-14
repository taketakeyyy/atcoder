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
    string S; cin >> S;
    ll N = S.size();

    // 各ビット列の分布を数える
    map<ll,ll> cnt; // 分布
    ll bit = 0;  // ビット列
    cnt[bit]++;
    for(ll i=0; i<N; i++) {
        ll num = S[i] - '0';
        bit ^= 1<<num;
        cnt[bit]++;
    }

    // 分布から答えを計算する
    ll ans = 0;
    for(ll bit=0; bit<(1<<10); bit++) {
        if (cnt[bit] == 0) continue;
        ans += cnt[bit]*(cnt[bit]-1)/2;  // nC2
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}