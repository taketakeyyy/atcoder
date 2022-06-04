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


void solve() {
    ll N, K; cin >> N >> K;
    vector<ll> A(N);
    map<ll,set<ll>> mpa;
    for(ll i=0; i<N; i++) {
        cin >> A[i];
        mpa[A[i]].insert(i);
    }
    vector<ll> B = A;
    sort(B.begin(), B.end());

    for(ll i=0; i<N; i++) {
        ll t = B[i];
        ll t_idx = -1;
        for(ll idx: mpa[t]) {
            if (abs(i-idx)%K == 0) {
                t_idx = idx;
                break;
            }
        }

        if (t_idx != -1) {
            mpa[t].erase(t_idx);
        }
        else {
            cout << "No" << endl;
            return;
        }
    }
    cout << "Yes" << endl;
}

int main() {
    solve();
    return 0;
}