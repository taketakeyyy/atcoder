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
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


// 文字列を2分割する。これよく見るな？
// 前半部分の赤と青の塗り方を全探索
// 後半部分も赤と青の塗り方を全探索
// ・前半部分の赤で塗ったものを左から右へ読む == 後半部分の青で塗ったものを右から左へ読む
// ・前半部分の青で塗ったものを左から右へ読む == 後半部分の赤で塗ったものを右から左へ読む
// 上記2点を満たすものを数え上げたい。
// それぞれmapかなんかで分布をとり、分布で組み合わせを計算すればOK
// 右から左へ読むのは、文字列を反転して左から右へ読むようにすれば実装が簡単になる。
void solve() {
    ll N; string S; cin >> N >> S;

    // mp[(red,blue)] := (赤色文字列red, 青色文字列blue)の分布
    auto genMap = [&](ll l, ll r, bool is_flip) {
        // Sの[l,r)の部分を切り取った文字列をTとする
        string T = S.substr(l, r-l);
        ll NT = T.size();
        if (is_flip) reverse(T.begin(), T.end());

        // 塗り方を全探索する
        // unordered_map<pair<string,string>,ll,HashPair> mp; // (赤色文字列,青色文字列)の分布
        map<pair<string,string>,ll> mp; // (赤色文字列,青色文字列)の分布
        for(ll bit=0; bit<(1<<NT); bit++) {
            string red = ""; // 赤色の文字列
            string blue = ""; // 青色の文字列
            for(ll d=0; d<NT; d++) {
                if (bit>>d&1) {
                    red.push_back(T[d]);
                }
                else {
                    blue.push_back(T[d]);
                }
            }
            mp[{red,blue}]++;
        }
        return mp;
    };
    auto mp1 = genMap(0, (2*N)/2, false); // 前半部分
    auto mp2 = genMap((2*N)/2, 2*N, true); // 後半部分

    // 条件を満たすものを数え上げる
    ll ans = 0;
    for(const auto &[key1, val1]: mp1) {
        string red1 = key1.first;
        string blue1 = key1.second;
        ans += val1 * mp2[{blue1, red1}];
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}