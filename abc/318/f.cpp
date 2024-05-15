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
void chmax(ll& x, ll y) { x = max(x,y); }
void chmin(ll& x, ll y) { x = min(x,y); }
string vs = "URDL";  // 上右下左
vector<ll> vy = { -1, 0, 1, 0 };
vector<ll> vx = { 0, 1, 0, -1 };


void solve() {
    ll N; cin >> N;
    vector<ll> X(N), L(N);
    for(ll i=0; i<N; i++) cin >> X[i];
    for(ll i=0; i<N; i++) cin >> L[i];

    // 判定が切り替わりうる点を列挙する
    set<ll> Pset;
    for(ll i=0; i<N; i++) {
        ll x = X[i];
        for(ll j=0; j<N; j++) {
            Pset.insert(x-L[j]);
            Pset.insert(x-L[j]+1);
            Pset.insert(x+L[j]);
            Pset.insert(x+L[j]+1);
        }
    }
    vector<ll> P(Pset.begin(), Pset.end());

    // 宝をすべての足で掴むことができるか判定 O(N logN)
    auto f = [&](ll k) { // kは頭の座標
        vector<ll> D(N); // 頭から宝までの距離
        for(ll i=0; i<N; i++) {
            D[i] = abs(k-X[i]);
        }
        sort(D.begin(), D.end());

        // 宝との距離が短いやつから、貪欲に短い足を割り当てる
        for(ll i=0; i<N; i++) {
            if (D[i] <= L[i]) continue;
            return false;
        }
        return true;
    };

    // イベントソート的な考え
    ll ans = 0;
    ll PN = P.size();
    ll pre_k = -INF;
    bool is_good = false; // すべての宝を足で掴むことが出来ている状態か
    for(ll i=0; i<PN; i++) {
        ll k = P[i];

        if (is_good) {
            if (f(k)) { // 判定OK -> OK のまま
                is_good = true;
                ans += (k-pre_k);
            }
            else {
                is_good = false;
            }
        }
        else {
            if (f(k)) { // 判定NG -> OK の切り替わった瞬間
                is_good = true;
                ans += 1;
            }
            else {
                is_good = false;
            }
        }
        pre_k = k;
    }
    cout << ans << endl;
}


int main() {
    solve();
    return 0;
}