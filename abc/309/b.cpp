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
    ll N; cin >> N;
    vector<string> A(N);
    for(ll i=0; i<N; i++) {
        cin >> A[i];
    }
    vector<string> B = A;

    for(ll i=0; i<N; i++) {
        for(ll j=0; j<N; j++) {
            if(i==0) {
                if (j!=N-1) {
                    B[i][j+1] = A[i][j];
                }
                else {
                    B[i+1][N-1] = A[i][j];
                }
            }
            else if (j==N-1) {
                if (i==0) continue;
                if (i!=N-1) {
                    B[i+1][j] = A[i][j];
                }
                else {
                    B[N-1][j-1] = A[i][j];
                }
            }
            else if (i==N-1) {
                if (j==N-1) continue;
                if (j!=0) {
                    B[i][j-1] = A[i][j];
                }
                else {
                    B[i-1][j] = A[i][j];
                }
            }
            else if (j==0) {
                if (i==N-1) continue;
                if (i==0) continue;
                B[i-1][j] = A[i][j];
            }
        }
    }

    // 出力
    for(ll i=0; i<N; i++) cout << B[i] << endl;
}


int main() {
    solve();
    return 0;
}