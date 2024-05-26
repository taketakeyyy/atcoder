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


/**
 * @brief Z-Algorithm
 * 各iについて、S と S.substr(i)の共通接頭辞の長さを格納した配列Zを求める。
 *
 * @tparam T
 * @param S 文字列S
 * @return vector<T> 各iについて共通接頭辞の長さを格納した配列Zを返す。
 */
template <typename T>
vector<T> z_algorithm(string S) {
    T n = S.size();
    vector<T> z(n, 0);
    z[0] = n;

    T i=1, j=0;
    while(i < n) {
        while(i+j<n && S[j]==S[i+j]) j++;
        z[i] = j;

        if (j == 0) {
            i++; continue;
        }

        T k = 1;
        while(k<j && k+z[k]<j) {
            z[i+k] = z[k];
            k++;
        }
        i += k;
        j -= k;
    }

    return z;
}


void solve() {
    ll N; cin >> N;
    string S; cin >> S;
    ll ans = 0;

    // S.substr(i)に対してZアルゴリズムをする O(N^2)
    for(ll i=0; i<N; i++) {
        vector<ll> Z = z_algorithm<ll>(S.substr(i));
        for(ll j=1; j<(ll)Z.size(); j++) {
            if (Z[j]>j) chmax(ans, j);
            else chmax(ans, Z[j]);
        }
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}