#define _USE_MATH_DEFINES  // M_PI等のフラグ
#include <bits/stdc++.h>
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) ((a+(b-1))/(b))
using namespace std;
using ll = long long;
const long long INF = LONG_LONG_MAX - 1'001'001'001'001'001;
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };
//ordered_set
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// 初項a, 末項l, 項数n のときの等差数列の和
ll tousa1(const ll &a, const ll &l, const ll &n) { return ((a+l)*n)/2; }
// 初項a, 公差d, 項数n のときの等差数列の和
ll tousa2(const ll &a, const ll &d, const ll &n) { return ((2*a+(n-1)*d)*n)/2; }


void solve() {
    ll N; cin >> N;
    ll S; cin >> S;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];
    vector<ll> A2 = A;
    for(ll i=0; i<N; i++) {
        A2.push_back(A[i]);
    }

    // A2の累積和S2
    vector<ll> S2(2*N+1, 0LL);
    for(ll i=0; i<2*N; i++) {
        S2[i+1] = S2[i] + A2[i];
    }

    for(ll i=0; i<=N; i++) {
        // [i, i+N-1]のN個の和を一周とする
        ll T = S2[i+N] - S2[i];
        ll rest = S%T;

        // ll j = i;
        // while(rest > 0) {
        //     rest -= A2[j];
        //     j++;
        // }

        // if (rest == 0) {
        //     cout << "Yes" << endl;
        //     return;
        // }

        if (i-1 >= 0) {
            auto itr = lower_bound(S2.begin()+i, S2.end(), rest+S2[i-1]);
            if (*itr == rest+S2[i-1]) {
                cout << "Yes" << endl;
                return;
            }
        }
        else {
            auto itr = lower_bound(S2.begin(), S2.end(), rest);
            if (*itr == rest) {
                cout << "Yes" << endl;
                return;
            }
        }
    }
    cout << "No" << endl;
}


int main() {
    solve();
    return 0;
}