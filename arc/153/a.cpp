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

// s1 s2 s3 s4 s5 s6 s7 s8 s9
// (s1,s2),(s5,s6),(s7,s9)のペアは同じ数字なので、
// s2, s6, s9 を消して、
// s1 s3 s4 s5 s7 s8 と圧縮できる。
// この圧縮数字のN番目の数を求める。
void solve() {
    ll N; cin >> N;
    N--;
    ll s8 = N%10;  // 1の位の数
    ll s7 = (N%100)/10;  // 10の位の数
    ll s5 = (N%1000)/100;  // 100の位の数
    ll s4 = (N%10000)/1000;  // 1000の位の数
    ll s3 = (N%100000)/10000;  // 10000の位の数
    ll s1 = (N%1000000)/100000; // 100000の位の数
    s1 += 1;

    cout << s1 << s1 << s3 << s4 << s5 << s5 << s7 << s8 << s7 << endl;
}


int main() {
    solve();
    return 0;
}