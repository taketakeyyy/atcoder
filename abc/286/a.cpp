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
    ll N, P, Q, R, S; cin >> N >> P >> Q >> R >> S;
    P--; Q--; R--; S--;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];


    vector<ll> tmpP;
    for(ll i=P; i<=Q; i++) {
        tmpP.push_back(A[i]);
    }
    vector<ll> tmpR;
    for(ll i=R; i<=S; i++) {
        tmpR.push_back(A[i]);
    }

    // 出力
    ll i = 0;
    while(i<N) {
        if (i == P) {
            for(ll a: tmpR) {
                cout << a << " ";
            }
            i = Q+1;
            continue;
        }
        if (i == R) {
            for(ll a: tmpP) {
                cout << a << " ";
            }
            i = S+1;
            continue;
        }
        cout << A[i] << " ";
        i++;
    }
    cout << endl;
}


int main() {
    solve();
    return 0;
}