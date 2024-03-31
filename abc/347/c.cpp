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


// 解説AC
// 予定がないB日を探す解法
void solve() {
    ll N, A, B; cin >> N >> A >> B;
    ll W = A+B;
    vector<ll> D(N);
    for(ll i=0; i<N; i++) {
        cin >> D[i];
        D[i] %= W;
    }
    sort(D.begin(), D.end());
    D.push_back(W+D[0]);

    // D[i]とD[i+1]の間が、B日あるか？
    for(ll i=0; i<N; i++) {
        ll diff = D[i+1]-D[i];
        if (diff-1 >= B) {
            cout << "Yes" << endl;
            return;
        }
    }
    cout << "No" << endl;
}

// 解説AC
// 予定が詰まったA日を探す解法
void solve2() {
    ll N, A, B; cin >> N >> A >> B;
    ll W = A+B;
    vector<ll> D(N);
    for(ll i=0; i<N; i++) {
        cin >> D[i];
        D[i] %= W;
    }

    // 2周分結合する
    for(ll i=0; i<N; i++) {
        D.push_back(W+D[i]);
    }
    sort(D.begin(), D.end());

    for(ll i=0; i<N; i++) {
        ll l = D[i];
        ll r = D[i+N-1];
        if (r-l+1 <= A) {
            cout << "Yes" << endl;
            return;
        }
    }
    cout << "No" << endl;
}

int main() {
    // solve();
    solve2();
    return 0;
}