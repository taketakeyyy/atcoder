#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
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


void solve() {
    ll N, A, B; cin >> N >> A >> B;
    ll P, Q, R, S; cin >> P >> Q >> R >> S;

    ll L1, R1;
    L1 = max(1-A, 1-B);
    R1 = min(N-A, N-B);

    auto f1 = [&](ll i, ll j) {
        ll sx = A + L1;
        ll sy = B + L1;
        ll diff = i - sx;

        return (sy+diff == j);
    };

    ll L2, R2;
    L2 = max(1-A, B-N);
    R2 = min(N-A, B-1);

    auto f2 = [&](ll i, ll j) {
        ll sx = A + L2;
        ll sy = B - L2;
        ll diff = i - sx;
        return (sy-diff == j);
    };

    for(ll i=P; i<=Q; i++) {
        for(ll j=R; j<=S; j++) {
            if (f1(i, j) || f2(i, j)) {
                cout << "#";
            }
            else {
                cout << ".";
            }
        }
        cout << endl;
    }

}


int main() {
    solve();
    return 0;
}