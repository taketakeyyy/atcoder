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


void solve() {
    ll N, X; cin >> N >> X;
    vector<ll> A;
    for(ll i=0; i<N-1; i++) {
        ll a; cin >> a;
        A.push_back(a);
    }
    sort(A.begin(), A.end());

    ll all_sum = 0;
    for(ll i=0; i<N-1; i++) {
        all_sum += A[i];
    }

    {// 0点取る場合
        ll total = all_sum - A.back();
        if (total >= X) {
            cout << 0 << endl;
            return;
        }
    }
    {// 中間の値を取る場合
        ll total = all_sum - A[0] - A.back();
        ll x = X - total;
        if (0<=x && x<=100 && x<=A.back() && x>=A[0]) {
            cout << x << endl;
            return;
        }
    }
    {// 大きい値を取る場合
        ll total = all_sum - A[0];
        if (total >= X) {
            cout << A.back() << endl;
            return;
        }
    }
    cout << -1 << endl;
}


int main() {
    solve();
    return 0;
}