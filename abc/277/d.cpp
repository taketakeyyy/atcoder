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


void solve() {
    ll N, M; cin >> N >> M;
    vector<ll> A(N);
    ll sumA = 0;
    for(ll i=0; i<N; i++) {
        cin >> A[i];
        sumA += A[i];
    }

    sort(A.begin(), A.end());

    // 各ブロックの和を数える
    vector<ll> block;
    ll pre = A[0];
    ll total = A[0];
    for(ll i=1; i<N; i++) {
        ll now = A[i];
        if (pre == now || pre+1 == now) {
            total += now;
            pre = now;
            continue;
        }
        else {
            block.push_back(total);
            total = now;
            pre = now;
        }
    }

    if (pre == M-1 && A[0]==0) {
        if (block.size() == 0) {
            block.push_back(total);
        }
        else {
            block[0] += total;
        }
    }
    else {
        block.push_back(total);
    }

    sort(block.begin(), block.end());
    reverse(block.begin(), block.end());

    // 出力
    ll ans = sumA - block[0];
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}