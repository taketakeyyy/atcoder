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
    ll N, M; cin >> N >> M;
    vector<vector<ll>> B(N, vector<ll>(M));
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<M; j++) {
            cin >> B[i][j];
            B[i][j]--;
        }
    }

    // ll ii = B[0][0]/7;
    // ll jj = B[0][0]%7;
    // bool is_ok = true;
    // for(ll i=0; i<N; i++) {
    //     for(ll j=0; j<M; j++) {
    //         ll b = ii*7+(i*7) + (jj+j);
    //         if (!(B[i][j] == b)) {
    //             is_ok = false;
    //             break;
    //         }
    //     }
    // }

    ll sj = B[0][0]%7;
    ll si = (B[0][0]-sj)/7;
    ll sb = B[0][0];
    bool is_ok = true;
    for(ll i=0; i<N; i++) {
        for(ll j=0; j<M; j++) {
            ll b = sb + i*7 + j;
            if (j-1 >= 0 && ((B[i][j-1]%7+1) != (B[i][j]%7))) {
                is_ok = false;
                break;
            }
            if (B[i][j] != b) {
                is_ok = false;
                break;
            }
        }
    }

    if (is_ok) {
        cout << "Yes" << endl;
    }
    else {
        cout << "No" << endl;
    }
}


int main() {
    solve();
    return 0;
}