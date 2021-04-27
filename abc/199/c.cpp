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


void solve() {
    ll N; cin >> N;
    string S; cin >> S;

    bool flip = false;
    vector<pair<ll,ll>> ops;
    ll Q; cin >> Q;
    for(int q=0; q<Q; q++) {
        ll t, a, b; cin >> t >> a >> b;
        if (t==1) {
            if (flip) {
                if (a <= N) a = N+a;
                else a = a-N;
                if (b <= N) b = N+b;
                else b = b-N;
                ops.push_back(make_pair(a,b));
            }
            else {
                ops.push_back(make_pair(a,b));
            }
        }
        else {
            flip = !flip;
        }
    }

    // 実際に文字を入れ替える
    for(auto [a,b]: ops) {
        swap(S[a-1], S[b-1]);
    }
    if (flip) {
        string s, t;
        s = S.substr(0, N);
        t = S.substr(N, N);
        S = t + s;
    }
    cout << S << endl;
}


int main() {
    solve();
    return 0;
}