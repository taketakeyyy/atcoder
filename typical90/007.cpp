#include <bits/stdc++.h>
#define _USE_MATH_DEFINES  // M_PI等のフラグ
#define MOD 1000000007
#define COUNTOF(array) (sizeof(array)/sizeof(array[0]))
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define intceil(a,b) (a+(b-1))/b
using namespace std;
using ll = long long;
using pii = pair<int,int>;
using pll = pair<long,long>;
const long long INF = LONG_LONG_MAX - 1001001001001001;
void chmax(int& x, int y) { x = max(x,y); }
void chmin(int& x, int y) { x = min(x,y); }

bool judge(vector<ll> const& A, ll b, ll mid) {
    if (A[mid] <= b) {
        // より高いクラスへいきたい
        return true;
    }
    else {
        return false;
    }
}

void solve() {
    ll N; cin >> N;
    vector<ll> A(N);
    for(int i=0; i<N; i++) cin >> A[i];
    sort(A.begin(), A.end());

    ll Q; cin >> Q;
    for(int q=0; q<Q; q++) {
        ll b; cin >> b;

        // 2分探索で最も不満度が低くなるクラスを探す
        ll l=0; ll r=N-1;
        ll mid = (l+r)/2;
        while(abs(r-l) > 1) {  // 隣り合ったら終了
            if (judge(A, b, mid)) {
                l = mid;
            }
            else {
                r = mid;
            }
            mid = (l+r)/2;
        }
        // lかrが答え
        cout << min(abs(A[l]-b), abs(A[r]-b)) << endl;
    }
}


int main() {
    solve();
    return 0;
}