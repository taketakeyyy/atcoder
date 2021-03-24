#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) (a+(b-1))/b
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }

bool f(const ll &N, const ll mid, const vector<ll> &F, const vector<ll> &A, ll k) {
    bool is_ok = true;
    for(int i=0; i<N; i++) {
        ll n = mid / F[i];
        k -= max<ll>(0, A[i]-n);
        if (k<0) {
            is_ok = false;
            break;
        }
    }
    return is_ok;
}

void solve() {
    ll N, K; cin >> N >> K;
    // 積和最小の問題
    // 2つの数列AとBから1つずつ選び、A[i]*B[j]の和の最小値は？
    // 食べにくさが{10^16, 1, 1}で、消化コストが{1,10,10}、K=1のとき、消化コストを10=>9にするより、1=>0にして、0*10^16=0にしたほうが下がり幅が大きい
    // 消化コストはできるだけ0の数を多くする方針にする
    // 消化コストの割当は、消化コストが小さいやつは、食べにくさ大きいやつに割り当てる。

    // ...とは違って、この問題はA[i]*B[j]の最大値の最小を求める。
    // 成績を二分探索で決めて、その成績を作れるか判定していく
    vector<ll> A(N);
    vector<ll> F(N);
    for(int i=0; i<N; i++) cin >> A[i];
    for(int i=0; i<N; i++) cin >> F[i];
    sort(A.begin(), A.end());
    sort(F.rbegin(), F.rend());
    ll l = 0;
    ll r = A[N-1]*F[0];
    ll mid = (l+r)/2;
    while(abs(l-r)>1) {
        bool is_ok = f(N, mid, F, A, K);

        if (is_ok) {
            r = mid;
            mid = (l+r)/2;
        }
        else {
            l = mid;
            mid = (l+r)/2;
        }
    }
    // lかrが答え
    if (f(N, l, F, A, K)) {
        cout << l << endl;
    }
    else {
        cout << r << endl;
    }
}


int main() {
    solve();
    return 0;
}