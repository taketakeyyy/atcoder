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
    ll N, M; cin >> N >> M;
    vector<string> S(N);
    for(ll i=0; i<N; i++) cin >> S[i];

    sort(S.begin(), S.end());
    do {
        bool is_ok = true;

        for(ll i=0; i<N-1; i++) {
            ll diff = 0;
            for(ll j=0; j<M; j++) {
                if (S[i][j] != S[i+1][j]) diff++;
            }

            if (diff != 1) {
                is_ok = false;
                break;
            }
        }
        if (is_ok) {
            cout << "Yes" << endl;
            return;
        }

    }while (next_permutation(S.begin(), S.end()));
    cout << "No" << endl;
}


int main() {
    solve();
    return 0;
}