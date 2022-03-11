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


void divisor(ll a, set<ll> &divs) {
    // aの約数列挙
    for(ll i=1; i*i<=a; i++) {
        if (a%i == 0) {
            divs.insert(i);
            divs.insert(a/i);
        }
    }
}

void solve() {
    ll N, M; cin >> N >> M;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    set<ll> divs;
    for(ll i=0; i<N; i++) {
        divisor(A[i], divs);
    }

    // divsの倍数を落とすふるい
    vector<ll> ks;
    vector<bool> is_k(M+1, true);
    is_k[0] = false; is_k[1] = true;
    for(ll d: divs) {
        if (d == 1) continue;

        if (is_k[d]) {
            for(ll j=d; j<=M; j+=d) {
                is_k[j] = false;
            }
        }
    }

    // is_k[i] = trueのものは？
    for(ll i=1; i<=M; i++) {
        if (is_k[i]) ks.push_back(i);
    }

    // 出力
    cout << ks.size() << endl;
    for(ll i=0; i<ks.size(); i++) cout << ks[i] << endl;
}


int main() {
    solve();
    return 0;
}