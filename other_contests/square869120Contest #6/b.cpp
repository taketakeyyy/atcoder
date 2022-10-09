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


// 時間 = |入り口-A| + |A-B| + |B-出口|
// |A-B|は不変。
// |入り口-A|が最小となるのは、入り口をAにしたとき。
// |B-出口|が最小となるのは、入り口をBにしたとき。
// このAとBを全探索する
void solve1() {
    ll N; cin >> N;
    vector<ll> A(N), B(N);
    for(ll i=0; i<N; i++) {
        cin >> A[i] >> B[i];
    }

    // 全探索
    ll ans = INF;
    for(auto s: A) {  // 入り口をAから選ぶ
        for(auto g: B) {  // 出口をBから選ぶ
            ll total = 0;
            for(ll i=0; i<N; i++) {
                total += abs(s-A[i]) + abs(A[i]-B[i]) + abs(B[i]-g);
            }
            ans = min(ans, total);
        }
    }

    // 出力
    cout << ans << endl;
}


// (1) s -> a -> b -> g という経路の秒数は、
//     |s-a|+|a-b|+|b-g|
//
// 各買い物客i において、sigma_i(|s-ai|)を最小とするsの値は、aiの中央値になる。
// 同様に、sigma_i(|bi-g|)を最小とするgの値は、biの中央値になる。
//
// ※ (x-a0)+(x-a1)+...+(x-an)を最小とするxの値は、aiの中央値
//
// (2) s -> b -> a -> g という経路の秒数は、
//     |s-b|+|b-a|+|a-g|
//
// これは問題にa < bという制約があるので、(1)のsとgを逆にしただけなので、やらなくてよい
void solve2() {
    ll N; cin >> N;
    vector<ll> A(N), B(N);
    for(ll i=0; i<N; i++) {
        cin >> A[i] >> B[i];
    }

    // A[i]とB[i]の中央値をそれぞれs,gとする
    vector<ll> tmpA = A;
    vector<ll> tmpB = B;
    sort(tmpA.begin(), tmpA.end());
    sort(tmpB.begin(), tmpB.end());
    ll s = tmpA[N/2];
    ll g = tmpB[N/2];

    ll ans = 0;
    for(ll i=0; i<N; i++) {
        ans += abs(s-A[i]) + abs(A[i]-B[i]) + abs(B[i]-g);
    }

    // 出力
    cout << ans << endl;
}


int main() {
    // solve1();
    solve2();
    return 0;
}