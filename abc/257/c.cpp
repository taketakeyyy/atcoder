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
    ll N; cin >> N;
    string S; cin >> S;
    vector<ll> W(N);
    for(ll i=0; i<N; i++) { cin >> W[i]; }
    vector<ll> otona;
    vector<ll> kodomo;
    for(ll i=0; i<S.size(); i++) {
        if (S[i] == '0') {
            kodomo.push_back(W[i]);
        }
        else {
            otona.push_back(W[i]);
        }
    }

    if (otona.size()==0 || kodomo.size()==0) {
        cout << N << endl;
        return;
    }

    sort(kodomo.begin(), kodomo.end());
    sort(otona.begin(), otona.end());

    // ll wl = otona[0];
    // ll wr = kodomo[kodomo.size()-1];
    // if (wr <= wl) {
    //     cout << N << endl;
    //     return;
    // }

    ll ans = 0;
    for(ll i=0; i<otona.size(); i++) {
        ll oi = lower_bound(otona.begin(), otona.end(), otona[i]) - otona.begin();
        ll wrong = oi;
        ll ki = lower_bound(kodomo.begin(), kodomo.end(), otona[i]) - kodomo.begin();
        wrong += kodomo.size() - ki;
        ans = max(ans, N-wrong);
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}