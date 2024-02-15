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

// #include <boost/multiprecision/cpp_int.hpp> // 多倍長整数
// using namespace boost::multiprecision; // 多倍長整数の cpp_int 型が使える

// 多倍長整数解法。TLE
// void solve() {
//     ll N; cin >> N;
//     vector<cpp_int> A(N);
//     map<cpp_int,ll> mp; // mp[a] := aがある個数

//     for(ll i=0; i<N; i++) {
//         cpp_int a; cin >> a;
//         A[i] = a;
//         mp[a]++;
//     }

//     // 数え上げ
//     ll ans = 0;
//     for(ll k=0; k<N; k++) {
//         for(ll j=0; j<N; j++) {
//             if (A[k]%A[j]!=0) continue;
//             cpp_int ai = A[k]/A[j];
//             ans += mp[ai];
//         }
//     }
//     cout << ans << endl;
// }

// 解説AC ハッシュを使う
void solve2() {
    ll N; cin >> N;
    vector<string> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    // Aをハッシュ値にする
    const vector<ll> BIG_PRIMES = {1000000007, 1000000037, 1000000039, 1000000049, 1000000073};
    vector<vector<ll>> B(N); // B[i] := A[i]をいくつかの素数でハッシュ化したもののリスト
    for(ll i=0; i<N; i++) {
        string a = A[i];
        reverse(a.begin(), a.end());
        for(ll p: BIG_PRIMES) {
            ll pow10 = 1;
            ll res = 0;
            for(char c: a) {
                res += ((c-'0')*pow10)%p;
                res %= p;
                pow10 *= 10; pow10 %= p;
            }
            B[i].push_back(res);
        }
    }

    // B[i]の分布をとる
    map<vector<ll>,ll> cnt;
    for(ll i=0; i<N; i++) cnt[B[i]]++;

    // 数え上げ
    ll ans = 0;
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<N; j++) {
            vector<ll> Bks;
            for(ll pi=0; pi<(ll)BIG_PRIMES.size(); pi++) {
                ll Bk = (B[i][pi]*B[j][pi])%BIG_PRIMES[pi]; // オーバーフロー注意
                Bks.push_back(Bk);
            }
            ans += cnt[Bks];
        }
    }

    // 答え
    cout << ans << endl;
}


int main() {
    // solve();
    solve2();
    return 0;
}