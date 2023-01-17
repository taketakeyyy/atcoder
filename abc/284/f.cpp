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

// 解説AC
void solve() {
    ll N; cin >> N;
    string T; cin >> T;

    string half1 = T.substr(0,N);
    string half2 = T.substr(N);
    reverse(half2.begin(), half2.end());

    string a = half1 + half2;
    string b = half2 + half1;

    auto za = z_algorithm<ll>(a);
    auto zb = z_algorithm<ll>(b);

    for(ll i=0; i<=N; i++) {
        if (i!=0 && za[2*N-i]!=i) continue;
        ll j = N - i;
        if (j!=0 && zb[2*N-j] != j) continue;
        // 答えが見つかった
        cout << a.substr(0,i);
        reverse(b.begin(), b.end());
        cout << b.substr(0,j);
        cout << endl;
        cout << i << endl;
        return;
    }
    cout << -1 << endl;
}

// blog用の解答
void solve2() {
    ll N; cin >> N;
    string T; cin >> T;

    string half1 = T.substr(0,N);
    string half2 = T.substr(N,N);
    reverse(half2.begin(), half2.end());

    // 答えが0文字のとき
    if (half1 == half2) {
        cout << T.substr(N,N) << endl;
        cout << 0 << endl;
        return;
    }

    string a = half1 + half2;
    string b = half2 + half1;

    auto za = z_algorithm<ll>(a);
    auto zb = z_algorithm<ll>(b);

    for(ll i=0; i<N; i++) {
        if (za[2*N-(i+1)] == i+1) {
            ll j = N-i-1;
            if (zb[2*N-j] == j) {
                // 答えが見つかった
                cout << a.substr(0,i+1);
                reverse(b.begin(), b.end());
                cout << b.substr(0,j);
                cout << endl;
                cout << i+1 << endl;
                return;
            }
        }
    }
    cout << -1 << endl;
}


int main() {
    // solve();
    solve2();
    return 0;
}