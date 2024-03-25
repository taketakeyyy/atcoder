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


// 不変量を見る解法：TLE
void solve() {
    ll N; cin >> N;
    string S; cin >> S;
    vector<ll> A(N+1);
    for(ll i=1; i<=N; i++) {
        A[i] = S[i-1]-'0';
    }

    // aとbの否定論理積を返す
    auto nega_con = [&](ll a, ll b) {
        ll c = a&b;
        if (c==0) return 1;
        return 0;
    };

    vector<ll> f1(N+1); // f(1,i)の値
    vector<ll> rui(N+1); // f(1,i)の累積和
    rui[0] = 0;
    f1[1] = A[1];
    rui[1] = A[1];
    for(ll i=2; i<=N; i++) {
        f1[i] = nega_con(f1[i-1], A[i]);
        rui[i] = rui[i-1] + f1[i];
    }

    // 不変量を見る。ほとんど変わらないので、変わった部分のみを再計算
    ll ans = 0;
    for(ll i=1; i<=N; i++) {
        ll total = 0;
        ll fi = A[i]; // f(i,j)の値
        for(ll j=i; j<=N; j++) {
            if (f1[j]==fi) {
                // 一致したら、それ以降はf(1,i)のときと計算結果は変わらないので、累積和が使える
                total += rui[N]-rui[j-1];
                break;
            }
            else {
                // 変わった部分のみを再計算
                total += fi;
                fi = nega_con(fi, A[j+1]);
            }
        }
        ans += total;
    }
    cout << ans << endl;
}

// 解説AC
// 「数列Aの末尾に0か1を追加したときに、答えがどう変わるか？」解法
void solve2() {
    ll N; cin >> N;
    string S; cin >> S;

    ll ans = 0;
    vector<ll> cnt(2, 0); // cnt[n] := 前回のNANDの答えがnの個数
    for(ll i=0; i<N; i++) {
        ll x = S[i]-'0';

        if (x==0) {
            cnt[0] = 1;
            cnt[1] = i+1-1;
        }
        else {
            swap(cnt[0], cnt[1]);
            cnt[1]++;
        }
        ans += cnt[1];
    }
    cout << ans << endl;
}

int main() {
    // solve();
    solve2();
    return 0;
}