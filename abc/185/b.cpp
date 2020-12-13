#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;
using ll = long long;
using pii = pair<int,int>;
const int INF = 1001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }


void solve(){
    long long N, M;
    long long T;
    cin >> N >> M >> T;
    long long now = 0LL;
    long long rest = N;
    for (long long i=0LL; i<M; i++) {
        long long a, b;
        cin >> a >> b;
        rest -= a-now;
        if (rest <= 0LL) {
            cout << "No" << endl;
            return;
        }
        rest += (b-a);
        if (rest > N) rest = N;
        now = b;
    }
    rest -= T-now;
    if (rest <= 0LL) {
        cout << "No" << endl;
        return;
    }
    cout << "Yes" << endl;

}


int main(int argc, char const *argv[]){
    solve();
    return 0;
}