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
    ll N, K; cin >> N >> K;
    vector<ll> A(N);
    for(ll i=0; i<N; i++) cin >> A[i];

    vector<ll> adds;
    ll xpn;
    set<ll> xpn_sets;
    ll X = 0;
    ll k = 0;
    while(1) {
        if (k == K) {
            cout << X << endl;
            return;
        }
        k++;

        // X%Nの計算
        xpn = X%N;
        if (xpn_sets.count(xpn)) {  // 周期が発生した
            break;
        }
        xpn_sets.insert(xpn);

        // 皿にアメを追加
        X += A[xpn];

        adds.push_back(A[xpn]);
    }

    // 周期を計算
    ll addstotal = 0;
    ll t = 0;
    ll start;
    for(ll i=0; i<adds.size(); i++) {
        if (adds[i] == A[xpn]) {
            // iからスタートしてぐるぐる回る
            start = i;
            for(ll j=start; j<adds.size(); j++) {
                addstotal += adds[j];
            }
            t = adds.size() - i;
            break;
        }
    }

    K -= k-1;
    X += (K/t)*addstotal;
    ll rest = K%t;
    for(ll j=start; j<start+rest; j++) {
        X += adds[j];
    }
    cout << X << endl;
}


int main() {
    solve();
    return 0;
}