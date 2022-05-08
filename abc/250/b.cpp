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
    ll N, A, B; cin >> N >> A >> B;
    ll start_color = 0;
    for(ll h=0; h<A*N; h++) {
        if ((h>0) && (h%A==0)) {
            start_color ^= 1;
        }

        ll color = start_color;
        for(ll w=0; w<B*N; w++) {
            if ((w>0) && (w%B==0)) {
                color ^= 1;
            }

            if(color == 0) {
                cout << ".";
            }
            else {
                cout << "#";
            }
        }
        cout << endl;
    }
}


int main() {
    solve();
    return 0;
}