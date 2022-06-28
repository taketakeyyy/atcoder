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

ll f(ll x, ll i, const vector<ll> &ruiseki) {
    return ruiseki[x] - ruiseki[i];
}

void solve() {
    ll N; cin >> N;
    vector<ll> A(N);
    ll total = 0;
    for(ll i=0; i<N; i++) {
        cin >> A[i];
        total += A[i];
    }

    if (total%10 != 0) {
        cout << "No" << endl;
        return;
    }

    // 円環を2倍にしてつなげる
    vector<ll> AA;
    AA.insert(AA.end(), A.begin(), A.end());
    AA.insert(AA.end(), A.begin(), A.end());

    // 累積和
    vector<ll> ruiseki(AA.size()+1, 0);
    for(ll i=0; i<AA.size()-1; i++) {
        ruiseki[i+1] = ruiseki[i] + AA[i];
    }

    // 2分探索
    for(ll i=0; i<N; i++) {
        ll l = i;
        ll r = l+N;
        while(r-l != 1) {
            ll mid = (r+l)/2;
            if (f(mid, i, ruiseki) >= total/10) {
                r = mid;
            }
            else {
                l = mid;
            }
        }
        // l or r
        if (f(r, i, ruiseki) == total/10) {
            cout << "Yes" << endl;
            return;
        }
        if (f(l, i, ruiseki) == total/10) {
            cout << "Yes" << endl;
            return;
        }
    }
    cout << "No" << endl;

}


int main() {
    solve();
    return 0;
}