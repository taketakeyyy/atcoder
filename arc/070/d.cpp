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


// 参考:https://drken1215.hatenablog.com/entry/2020/10/06/113600

void solve() {
    ll N, K; cin >> N >> K;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) { cin >> A[i]; }

    // left[i][x] := 左からi個目まで見て、総和をxにできるか
    vector left(N+1, vector<bool>(K+1, false));
    // right[i][x] := 右からi個目まで見て、総和をxにできるか
    vector right = left;
    left[0][0] = right[0][0] = true;
    for(ll i=0; i<N; i++) {
        for(ll x=0; x<=K; x++) {
            if (left[i][x]) {
                left[i+1][x] = true;
                if (x+A[i] <= K) { left[i+1][x+A[i]] = true; }
            }
            if (right[i][x]) {
                right[i+1][x] = true;
                if (x+A[N-1-i] <= K) { right[i+1][x+A[N-1-i]] = true; }
            }
        }
    }

    // 今、不必要なものの数を数えたい。
    // 整数A[i]が不必要であることは、
    // * A[i]以外のN-1個の整数の部分集合であって、
    // * 総和が [K-A[i], K) となるものは存在しない
    // ということ。
    // このことは事前にleft, right を求めたことによって、
    // * 各iについて、
    // * left[i][x]=trueであるような任意のx(<K)について、
    // * v = K-x-A[i], ... , K-x-1 のいずれについても、right[N-1-i][v] がfalseであるかを判定する
    // に言い換えられる。
    ll ans = 0;
    for(ll i=0; i<N; i++) {
        vector<ll> sum(K+2, 0);  // rightの累積和
        for(ll x=0; x<=K; x++) { sum[x+1] = sum[x] + right[N-1-i][x]; }
        bool is_ok = true;
        for(ll x=0; x<K; x++) {
            if (!left[i][x]) { continue; }
            if (sum[K-x] - sum[max(0LL, K-x-A[i])] > 0) { is_ok = false; }
        }
        if (is_ok) ans++;
    }

    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}